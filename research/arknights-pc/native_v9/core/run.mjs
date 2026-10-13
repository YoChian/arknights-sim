import fs from 'node:fs/promises';
import path from 'node:path';
import {spawn,execFile} from 'node:child_process';
import {promisify} from 'node:util';
const execFileAsync=promisify(execFile);
const root='D:\\Repo\\.rea-tools\\arknights-pc\\native_v9\\core';
const ghidra='D:\\Repo\\.rea-tools\\ghidra\\ghidra_12.1.4_PUBLIC';
const java='D:\\Android Studio\\jbr\\bin\\java.exe';
const tag=process.argv[2]||'round1';
if(!/^round[0-9]+$/.test(tag))throw new Error('Invalid analysis tag');
for(const d of ['home','tmp','appdata','localappdata'])await fs.mkdir(path.join(root,d),{recursive:true});
const project='D:\\Repo\\arknights-ghidra-work\\native-v9-project';
await fs.mkdir(project,{recursive:true});
const env={...process.env,JAVA_HOME:'D:\\Android Studio\\jbr',APPDATA:path.join(root,'appdata'),LOCALAPPDATA:path.join(root,'localappdata')};
const iso=['-Duser.home='+path.join(root,'home'),'-Djava.io.tmpdir='+path.join(root,'tmp')];
const support=await execFileAsync(java,[...iso,'-cp',path.join(ghidra,'support','LaunchSupport.jar'),'LaunchSupport',ghidra,'-vmargs'],{env,windowsHide:true,maxBuffer:1024*1024});
const vm=support.stdout.split(/\r?\n/).filter(Boolean);
if(vm.some(s=>!s.startsWith('-')||s.includes('\0')))throw new Error('Unexpected JVM argument');
const sourceInput=path.join(root,'input.json'),input=path.join(root,'input_'+tag+'.json'),output=path.join(root,'results_'+tag+'.json');
await fs.copyFile(sourceInput,input);
const args=[...vm,'-Xmx1536M','-XX:ParallelGCThreads=1','-Djava.awt.headless=true',...iso,
 '-cp',path.join(ghidra,'Ghidra','Framework','Utility','lib','Utility.jar'),'ghidra.Ghidra','ghidra.app.util.headless.AnalyzeHeadless',
 project,'NativeV9_'+tag,'-import','D:\\Hypergryph Launcher\\games\\Arknights\\GameAssembly.dll','-noanalysis','-readOnly','-deleteProject',
 '-max-cpu','1','-log',path.join(root,'ghidra_'+tag+'.log'),'-scriptlog',path.join(root,'script_'+tag+'.log'),
 '-scriptPath',root,'-postScript','ArknightsFocused.java',input,output];
await fs.writeFile(path.join(root,'launch_'+tag+'.json'),JSON.stringify({java,ghidra,input,output,scope:'selected static PE unwind ranges, no default autoanalysis or game execution'},null,2));
console.log(JSON.stringify({phase:'launch',tag}));
const log=await fs.open(path.join(root,'console_'+tag+'.log'),'w');
const child=spawn(java,args,{cwd:root,env,windowsHide:true,stdio:['ignore','pipe','pipe']});
await fs.writeFile(path.join(root,'process_'+tag+'.json'),JSON.stringify({parent_pid:process.pid,child_pid:child.pid,root,tag,java,started_at:new Date().toISOString()},null,2));
function consume(c){log.write(c);for(const l of c.toString().split(/\r?\n/))if(/FOCUSED_|ERROR|Exception|Importing|REPORT:/.test(l))console.log(l.slice(0,1500));}
child.stdout.on('data',consume);child.stderr.on('data',consume);
const code=await new Promise((resolve,reject)=>{child.once('error',reject);child.once('close',resolve);});
await log.close();
console.log(JSON.stringify({phase:'done',exitCode:code,output}));
if(code!==0)process.exitCode=1;
