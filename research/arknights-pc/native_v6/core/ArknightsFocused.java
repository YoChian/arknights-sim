// Bounded, execution-free analysis of explicitly selected native entry candidates.
// @category Arknights
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.security.MessageDigest;

public class ArknightsFocused extends GhidraScript {
  public void run() throws Exception {
    String[] args=getScriptArgs();
    JsonObject input=JsonParser.parseString(Files.readString(Path.of(args[0]),StandardCharsets.UTF_8)).getAsJsonObject();
    JsonObject result=new JsonObject();
    result.addProperty("target_sha256",currentProgram.getExecutableSHA256());
    if(!currentProgram.getExecutableSHA256().equals(input.get("target_sha256").getAsString()))throw new Exception("Target SHA256 mismatch");
    result.addProperty("analysis_mode","explicit selected PE function ranges; default whole-image analysis disabled");
    result.addProperty("symbol_provenance",input.get("provenance").getAsString());
    Map<String,String> labels=new HashMap<>();
    try(var lines=Files.lines(Path.of(input.get("labels_path").getAsString()),StandardCharsets.UTF_8)){
      lines.forEach(line->{String[] s=line.split("\\t",2);if(s.length==2)labels.put(s[0],s[1]);});
    }
    if(input.has("seed_labels")){
      for(var entry:input.getAsJsonObject("seed_labels").entrySet()){
        Address address=toAddr(entry.getKey());
        currentProgram.getSymbolTable().createLabel(address,entry.getValue().getAsString(),SourceType.USER_DEFINED).setPrimary();
      }
    }
    JsonArray output=new JsonArray();
    DecompInterface decompiler=new DecompInterface();
    decompiler.setOptions(new DecompileOptions());
    decompiler.toggleCCode(true);
    decompiler.toggleSyntaxTree(true);
    decompiler.openProgram(currentProgram);
    try {
      for(JsonElement item:input.getAsJsonArray("targets")){
        monitor.checkCancelled();
        JsonObject target=item.getAsJsonObject();
        String name=target.get("name").getAsString();
        Address start=toAddr(target.get("address").getAsString());
        Address end=toAddr(target.get("end_address").getAsString());
        AddressSet body=new AddressSet();
        if(target.has("ranges")){
          for(JsonElement piece:target.getAsJsonArray("ranges")){
            JsonObject range=piece.getAsJsonObject();
            body.addRange(toAddr(range.get("start").getAsString()),toAddr(range.get("end").getAsString()));
          }
        }else body.addRange(start,end);
        JsonObject row=target.deepCopy();
        println("FOCUSED_START "+target.get("display_name").getAsString()+" "+start);
        try {
          if(target.has("ranges")){
            JsonArray checks=new JsonArray();
            for(JsonElement piece:target.getAsJsonArray("ranges")){
              JsonObject range=piece.getAsJsonObject();
              if(!range.has("source_sha256"))continue;
              Address begin=toAddr(range.get("start").getAsString());
              Address last=toAddr(range.get("end").getAsString());
              byte[] bytes=new byte[(int)(last.subtract(begin)+1)];
              int read=currentProgram.getMemory().getBytes(begin,bytes);
              String actual=HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(bytes));
              boolean same=read==bytes.length&&actual.equals(range.get("source_sha256").getAsString());
              JsonObject check=new JsonObject();
              check.addProperty("start",range.get("start").getAsString());
              check.addProperty("bytes",read);check.addProperty("imported_sha256",actual);check.addProperty("match",same);checks.add(check);
              if(!same)throw new Exception("Imported memory differs from source range "+begin);
            }
            row.add("imported_range_checks",checks);
            row.addProperty("imported_memory_matches_source",true);
          }
          boolean decoded=new DisassembleCommand(start,body,true).applyTo(currentProgram,monitor);
          row.addProperty("disassembled",decoded);
          Function func=currentProgram.getFunctionManager().getFunctionAt(start);
          if(func==null)func=currentProgram.getFunctionManager().createFunction(name,start,body,SourceType.USER_DEFINED);
          else {func.setName(name,SourceType.USER_DEFINED);func.setBody(body);}
          JsonArray calls=new JsonArray();
          InstructionIterator iterator=currentProgram.getListing().getInstructions(body,true);
          int instructions=0;
          while(iterator.hasNext()){
            Instruction ins=iterator.next();instructions++;
            if(!ins.getFlowType().isCall())continue;
            for(Reference ref:ins.getReferencesFrom()){
              if(!ref.getReferenceType().isCall())continue;
              Address dst=ref.getToAddress();
              String key="0x"+Long.toHexString(dst.getOffset());
              String calleeName=labels.get(key);
              if(calleeName!=null){
                Function callee=currentProgram.getFunctionManager().getFunctionAt(dst);
                if(callee!=null)callee.setName(calleeName,SourceType.USER_DEFINED);
                else currentProgram.getSymbolTable().createLabel(dst,calleeName,SourceType.USER_DEFINED).setPrimary();
              }
              JsonObject call=new JsonObject();call.addProperty("source",ins.getAddress().toString());call.addProperty("target",key);call.addProperty("candidate_name",calleeName);calls.add(call);
            }
          }
          row.addProperty("instruction_count",instructions);
          row.add("direct_calls",calls);
          decompiler.flushCache();
          DecompileResults dr=decompiler.decompileFunction(func,60,monitor);
          row.addProperty("decompile_completed",dr.decompileCompleted());
          row.addProperty("decompiler_message",dr.getErrorMessage());
          if(dr.decompileCompleted())row.addProperty("pseudocode",dr.getDecompiledFunction().getC());
        }catch(Exception ex){row.addProperty("error",ex.toString());}
        output.add(row);
        result.add("functions",output);
        Files.writeString(Path.of(args[1]),new GsonBuilder().setPrettyPrinting().serializeNulls().create().toJson(result),StandardCharsets.UTF_8);
        println("FOCUSED_DONE "+name);
      }
    }finally{decompiler.dispose();}
  }
}
