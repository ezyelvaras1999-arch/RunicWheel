// Offline layout check (v0.27). Compiled ONLY with /DRUNIC_LAYOUT_DUMP into a test DLL,
// never into the release: it fills a sample wheel, runs the real draw_labels() or
// khaos_draw_menu() and writes the vertex buffers, which tools/sim/render_layout.py
// rasterises with the real atlases. Nothing here touches the game.
#ifdef RUNIC_LAYOUT_DUMP
static void dump_write(Handle f,const void* p,DWord n){DWord done=0;(void)WriteFile(f,p,n,&done,nullptr);}
static void dump_name(unsigned w,unsigned s,unsigned i,const char* text){
    char* out=g_displayNames[w][s][i];unsigned n=0;
    while(text[n] && n<rw12ui::NameBytes-1){out[n]=text[n];++n;}
    out[n]=0;
}
extern "C" __declspec(dllexport) int __cdecl RunicLayoutDump(int width,int height,int scenario,int textScale,const char* path){
    // Non-null atlas handles: the layout code only tests them, the dump never draws.
    g_fontAtlas=g_plaqueAtlas=g_frameAtlas=(Raw)1;g_iconAtlas=nullptr;g_firstThemeEnabled=0;
    g_textScalePercent=textScale;g_showNames=1;g_showWheelTitles=1;g_showWheelOccupancy=1;
    g_showNextPreview=1;g_showEditorHelp=1;g_enableAdvancedEditor=1;g_showWheelControlsGuide=1;
    g_model=rw05::State{};
    rw05::Binding a{};a.formId=0x0002ACD3;a.kind=rw05::Spell;
    rw05::Binding b{};b.formId=0x00045F9C;b.kind=rw05::Spell;
    rw05::Binding c{};c.formId=0x0001C4E6;c.kind=rw05::Weapon;
    (void)rw05::add(g_model.slot[0][0],a);(void)rw05::add(g_model.slot[0][0],b);
    (void)rw05::add(g_model.slot[0][1],c);
    g_model.cursor[0][0]=1;
    dump_name(0,0,0,"CHAIN LIGHTNING");
    dump_name(0,0,1,scenario==3?"FIRE":"CIRCLE OF PROTECTION");
    dump_name(0,1,0,"EBONY BLADE");
    g_iconIndices[0][0][1]=rw14::Restoration;
    InterlockedExchange(&g_activeWheel,0);InterlockedExchange(&g_select,0);
    InterlockedExchange(&g_menuFlags,scenario==1?1:0);
    g_khaosFontOverride=0;
    if(scenario==2){g_khaosFontOverride=1;khaos_begin_session();khaos_draw_menu(width,height);g_khaosFontOverride=0;}
    else draw_labels((float)width,(float)height);
    Handle f=CreateFileA(path,0x40000000u,0,nullptr,2,0x80,nullptr);
    if(f==(Handle)(-1))return 0;
    const Long counts[4]={(Long)g_labelVert,(Long)g_fontVertexCount,6,6};
    dump_write(f,counts,sizeof counts);
    dump_write(f,g_labels,(DWord)(sizeof(Vertex)*g_labelVert));
    dump_write(f,g_fontQuads,(DWord)(sizeof(TextureVertex)*g_fontVertexCount));
    dump_write(f,g_plaqueQuads,(DWord)(sizeof(TextureVertex)*6));
    dump_write(f,g_frameQuads,(DWord)(sizeof(TextureVertex)*6));
    CloseHandle(f);
    return 1;
}
#endif
