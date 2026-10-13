// Independent branch/accounting translation; no Unity or game assemblies.
using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Web.Script.Serialization;

class NpcLifecycleReference {
    static object[] A(object value){return value is ArrayList?((ArrayList)value).ToArray():(object[])value;}
    static bool B(Dictionary<string,object> r,string k){return Convert.ToBoolean(r[k]);}
    static int I(Dictionary<string,object> r,string k){return Convert.ToInt32(r[k]);}
    static float F(Dictionary<string,object> r,string k){return Convert.ToSingle(r[k]);}
    static int[] Counters(Dictionary<string,object> r) {
        var input=A(r["counters"]);var c=new int[5];
        for(int i=0;i<5;i++)c[i]=Convert.ToInt32(input[i]);
        bool death=I(r,"reason")==2;
        unchecked {
            if(!B(r,"dont_count")&&!B(r,"is_summon")) {
                ++c[0];if(B(r,"always_count")||death)++c[1];
                if(B(r,"is_override")) {
                    int n=I(r,"override_count");
                    if(n>0)++c[2];
                    if(death){c[3]+=n;if(c[3]<0)c[3]=0;}
                    else if(n>0)++c[4];
                } else if(!B(r,"invalid")) {
                    ++c[2];if(death)++c[3];else ++c[4];
                }
            }
            if(B(r,"is_summon")&&!B(r,"unharmful")&&!death)++c[4];
        }
        return c;
    }
    static void Add(List<object> log,string name,int frame,int uid) {
        log.Add(new object[]{name,frame,uid});
    }
    static Dictionary<string,object> Lifetime(Dictionary<string,object> r) {
        int reason=I(r,"reason");bool death=reason==2,flag=B(r,"recycle_flag");
        float delay=F(r,"delay");var log=new List<object>();int uid=24;
        int wave=B(r,"dont_block")?0:1,final=1,missed=0,frame=0;bool recycled=false;
        if(death) {
            Add(log,"dead_state_release_block",0,uid);
            if(B(r,"specific")&&B(r,"animation_found"))delay=F(r,"animation_length");
            Add(log,"dead_state_animation_provider",0,uid);
        }
        Add(log,"enemy_log_runtime_snapshot",0,uid);Add(log,"enemy_stats_finish",0,uid);
        if(death)Add(log,"enemy_death_extra_log",0,uid);
        Add(log,"state_machine_stop",0,uid);
        if(death){if(B(r,"source_exists"))Add(log,"source_on_target_killed",0,uid);Add(log,"entity_event1",0,uid);}
        Add(log,"buff_owner_finish",0,uid);Add(log,"buff_clear",0,uid);
        Add(log,"entity_clear_abilities_hold_effects_ep",0,uid);Add(log,"entity_event2",0,uid);
        Add(log,"unit_finish_animator_mode_visual_cleanup",0,uid);
        if(!B(r,"dummy")) {Add(log,"battle_event6",0,uid);wave=0;if(!flag)final=0;if(!death&&!B(r,"unharmful"))missed++;}
        Add(log,"enemy_level_event3_tile_block_skill_cleanup",0,uid);
        Add(log,"default_mode_destroy_entity",0,uid);
        bool deferred=death&&delay>(float)1e-5;
        if(deferred)Add(log,"delayed_recycle_started",0,uid);
        Action recycle=()=>{
            Add(log,"unit_recycle_dynamic_abilities_modes_unregister_talents_visual",frame,uid);
            Add(log,"entity_recycle_cleanup_clear_abilities",frame,uid);Add(log,"unregister_bobject",frame,uid);
            uid=0;Add(log,"uid_invalidated",frame,uid);Add(log,"enemy_reset_cursor_and_route",frame,uid);
            if(B(r,"ground")){Add(log,"ground_bound_recycle",frame,uid);Add(log,"battle_event8",frame,uid);if(flag)final=0;}
            recycled=true;Add(log,"raw_pool_recycled",frame,uid);
        };
        if(!deferred)recycle();
        Add(log,"mode_on_enemy_finished",0,uid);Add(log,"enemy_after_finish_gates",0,uid);
        if(deferred&&B(r,"owner_available")) {
            float quotient=(float)(delay/F(r,"delta"));
            frame=Math.Max(1,(int)Math.Round((double)quotient,MidpointRounding.ToEven));recycle();
        }
        return new Dictionary<string,object>{{"id",I(r,"id")},{"stages",log},{"recycled",recycled},
            {"uid",uid},{"wave",wave},{"final",final},{"valid_missed",missed},
            {"recycle_frame",recycled?frame:-1},{"delay",delay}};
    }
    static void Main(string[] args) {
        var json=new JavaScriptSerializer();json.MaxJsonLength=10000000;
        var input=json.Deserialize<Dictionary<string,object>>(File.ReadAllText(args[0]));
        var counters=new List<object>();var life=new List<object>();
        foreach(Dictionary<string,object> row in A(input["accounting"]))
            counters.Add(new Dictionary<string,object>{{"id",I(row,"id")},{"counters",Counters(row)}});
        foreach(Dictionary<string,object> row in A(input["lifetime"]))life.Add(Lifetime(row));
        var output=new Dictionary<string,object>{{"scope","independent C# branch/accounting/frame-count translation; not a Unity/client oracle or full IEnumerator implementation"},
            {"accounting",counters},{"lifetime",life}};
        File.WriteAllText(args[1],json.Serialize(output),new System.Text.UTF8Encoding(false));
    }
}
