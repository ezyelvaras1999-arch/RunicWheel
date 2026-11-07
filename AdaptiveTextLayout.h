#pragma once
// Pure bounded label-layout policy. No D3D/SKSE calls and no heap allocation.
// Used for player-facing names, including UTF-8 decoded into glyph indices by
// text_symbols(). A line stores glyph indices, never byte offsets: wrapping
// cannot split a multibyte character. It never replaces the suffix by an ellipsis.
namespace rw27text {
struct Line { unsigned begin=0, end=0; float width=0.f; };
struct Layout { unsigned count=0; Line lines[4]{}; float scale=0.f; float totalHeight=0.f; };
inline float smaller(float a,float b){return a<b?a:b;}
inline float larger(float a,float b){return a>b?a:b;}
inline bool is_blank(unsigned cp,unsigned space){return cp==space;}
// All metrics are in atlas units; requestedScale converts them to screen pixels.
inline Layout arrange(const unsigned* symbols,unsigned count,const unsigned char* advances,
                      unsigned space,unsigned hyphen,float requestedScale,float width,float height,
                      float capUnits,float gapUnits,unsigned maxLines=3,float fill=.88f) {
    Layout result{};
    if(!symbols||!advances||!count||width<=0||height<=0||requestedScale<=0)return result;
    if(count>78)count=78;
    if(maxLines>4)maxLines=4;
    if(!maxLines)return result;
    // Remove trailing/leading blanks once; interior blanks are trimmed at wraps.
    while(count && is_blank(symbols[count-1],space))--count;
    unsigned first=0;while(first<count && is_blank(symbols[first],space))++first;
    if(first==count)return result;
    const float capLimit=height*fill;
    float bestQuality=-1.f;
    for(unsigned k=1;k<=maxLines && k<=count-first;++k){
        float best[5][80];unsigned prev[5][80];
        for(unsigned r=0;r<=4;++r)for(unsigned j=0;j<=79;++j){best[r][j]=1.e30f;prev[r][j]=0;}
        best[0][first]=0.f;
        for(unsigned r=1;r<=k;++r)for(unsigned end=first+r;end<=count;++end){
            for(unsigned start=first+r-1;start<end;++start){
                if(best[r-1][start]>=1.e29f)continue;
                unsigned a=start,b=end;
                while(a<b && is_blank(symbols[a],space))++a;
                while(b>a && is_blank(symbols[b-1],space))--b;
                if(a>=b)continue;
                float line=0.f;
                for(unsigned j=a;j<b;++j)line+=(float)advances[symbols[j]];
                const bool midword=start>first && !is_blank(symbols[start-1],space) &&
                    !is_blank(symbols[start],space) && symbols[start-1]!=hyphen;
                // A word-boundary break is preferable, even if the lines are a
                // little unbalanced. Unbreakable words may still wrap safely.
                float cost=larger(best[r-1][start],line)+(midword?38.f:0.f);
                if(cost<best[r][end]){best[r][end]=cost;prev[r][end]=start;}
            }
        }
        if(best[k][count]>=1.e29f)continue;
        Layout candidate{};candidate.count=k;
        unsigned end=count;
        float widest=0.f;
        for(unsigned r=k;r>0;--r){
            unsigned start=prev[r][end],a=start,b=end;
            while(a<b && is_blank(symbols[a],space))++a;
            while(b>a && is_blank(symbols[b-1],space))--b;
            if(a>=b){candidate.count=0;break;}
            float units=0.f;for(unsigned j=a;j<b;++j)units+=(float)advances[symbols[j]];
            candidate.lines[r-1]={a,b,units};
            widest=larger(widest,units);end=start;
        }
        if(!candidate.count || end!=first)continue;
        const float vertical=(float)k*capUnits+(float)(k-1)*gapUnits;
        candidate.scale=smaller(requestedScale,smaller(width/widest,capLimit/vertical));
        candidate.totalHeight=vertical*candidate.scale;
        // Prefer 1 or 2 lines when scale is similar. Longer names win extra
        // lines when readability gains outweigh the extra row.
        const float quality=candidate.scale*(1.f-.045f*(float)(k-1));
        if(quality>bestQuality){bestQuality=quality;result=candidate;}
    }
    return result;
}
}
