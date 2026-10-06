#include <stdio.h>
#include <stdlib.h>//ランダム関数使う
#include <string.h>//カード一覧に使うー(正/逆)を消す

void start();//最初の画面
void Guidance();//各テストの定型文
void cardUp(int a);//カード生成（上の部分）
void cardDown(int a);//カード生成（下の部分）
void output(int a,int n);//共通生成結果+カード生成（中間の部分）
void view1();//カード名前一覧
void view2();//カード情報見る
int loop();//モード切替

//グローバル変数
int b[3];//生成されるカード番号格納する
int w;//コマンド もらう 変数

struct TARTOR{
    int no;
    char name[44];
    char info[128];
    char decision[6];
};

//カードのデータ
struct TARTOR card[44] = {
        {0, "0. 愚人(正)", "新しい始まり、冒険、自由、自発性、無限の可能性", "YES"},
        {1, "0. 愚人(逆)", "軽率、無謀、無計画、ためらい、障害", "NO"},
        {2, "I. 魔術師(正)", "創造力、技能、実行力、機会、自信", "YES"},
        {3, "I. 魔術師(逆)", "優柔不断、詐欺、不発、誤解、不満", "NO"},
        {4, "II. 女教皇(正)", "直感、秘密、知恵、静寂、潜在意識", "中立"},
        {5, "II. 女教皇(逆)", "表面的な知識、秘密の暴露、ヒステリー、無視", "NO"},
        {6, "III. 女帝(正)", "豊穣、母性、愛、美、繁栄", "YES"},
        {7, "III. 女帝(逆)", "停滞、過保護、浪費、成長の阻害", "中立"},
        {8, "IV. 皇帝(正)", "権威、秩序、安定、リーダーシップ、構造", "YES"},
        {9, "IV. 皇帝(逆)", "未熟、頑固、支配的、無秩序、無力", "NO"},
        {10, "V. 法王(正)", "伝統、調和、道徳、指導、社会ルール", "YES"},
        {11, "V. 法王(逆)", "孤立、偏狭、ルール違反、不信感", "中立"},
        {12, "VI. 恋人(正)", "愛、調和、選択、情熱、パートナーシップ", "YES"},
        {13, "VI. 恋人(逆)", "不調和、誤った選択、裏切り、対立", "NO"},
        {14, "VII. 戦車(正)", "勝利、意志力、自己コントロール、克服、進展", "YES"},
        {15, "VII. 戦車(逆)", "暴走、敗北、挫折、コントロール喪失", "NO"},
        {16, "VIII. 力量(正)", "勇気、忍耐、優しさ、自己制御、信念", "YES"},
        {17, "VIII. 力量(逆)", "自信過剰、自信喪失、無力感、感情的", "NO"},
        {18, "IX. 隠者(正)", "探求、省察、慎重、導き、孤独", "中立"},
        {19, "IX. 隠者(逆)", "閉鎖的、孤独感、偏執、引きこもり", "NO"},
        {20, "X. 運命の輪(正)", "幸運、転機、変化、チャンス、サイクル", "YES"},
        {21, "X. 運命の輪(逆)", "悪運、停滞、不測の事態、逆風", "NO"},
        {22, "XI. 正義(正)", "公平、バランス、誠実、決断、責任", "YES"},
        {23, "XI. 正義(逆)", "不公平、偏見、不正、責任回避", "NO"},
        {24, "XII. 吊られた男(正)", "試練、奉仕、新しい視点、忍耐、静止", "中立"},
        {25, "XII. 吊られた男(逆)", "無駄な犠牲、徒労、頑固、停滞", "NO"},
        {26, "XIII. 死神(正)", "終末、強制終了、転換期、再生、別れ", "NO"},
        {27, "XIII. 死神(逆)", "再起、執着の脱却、未練、新展開", "中立"},
        {28, "XIV. 節制(正)", "調和、自制、バランス、適応、純粋", "YES"},
        {29, "XIV. 節制(逆)", "不調和、過剰、浪費、不均衡", "NO"},
        {30, "XV. 悪魔(正)", "束縛、執着、誘惑、欲望、依存", "NO"},
        {31, "XV. 悪魔(逆)", "解放、覚醒、執着からの脱却、回復", "中立"},
        {32, "XVI. 塔(正)", "崩壊、突発的事件、災難、ショック、変革", "NO"},
        {33, "XVI. 塔(逆)", "緊迫状態、誤解、難の回避、余震", "NO"},
        {34, "XVII. 霊星(正)", "希望、霊感、癒やし、願い、前向き", "YES"},
        {35, "XVII. 霊星(逆)", "絶望、失望、疑念、自信喪失", "NO"},
        {36, "XVIII. 月(正)", "不安、迷い、幻影、胸騒ぎ、不透明", "NO"},
        {37, "XVIII. 月(逆)", "誤解解散、不安解消、開運、徐々に明瞭", "NO"},
        {38, "XIX. 太陽(正)", "成功、歓喜、情熱、活力、明晰", "YES"},
        {39, "XIX. 太陽(逆)", "遅延、不完全な成功、意欲低下", "YES"},
        {40, "XX. 審判(正)", "復活、覚醒、決断、結果、再生", "YES"},
        {41, "XX. 審判(逆)", "後悔、優柔不断、再起不能、現実逃避", "NO"},
        {42, "XXI. 世界(正)", "完成、成就、完璧、統合、旅行", "YES"},
        {43, "XXI. 世界(逆)", "未完成、未達成、限界、中途半端", "NO"}
    };

//mainプログラム
int main(void){
    while (1){
        start(); //最初の画面
        if(scanf("%d",&w)!=1){
            while (getchar() != '\n');{//数字以外入力NG
                printf("-----------数字を入力してください----------\n");
                continue;
            }
        }  
        switch (w){
            case 1:
                Guidance();
                printf("=======YES OR NO========\n");
                output(1,1);
                break;
            case 2:
                Guidance();
                printf("=======今日の運勢========\n");
                output(1,2);
                break;
            case 3:
                Guidance();
                printf("=======過去-現在-将来========\n");
                output(3,3);
                break;
            case 4:
                view1();
                view2();
                break;
            case 5:
                printf("終了です。\n");
                return 0;
            default:
                printf("-----------正しい数字(1-5)を入力してください----------\n");
                continue;
        }
        if(loop()==2){
           printf("終了です。\n");
           break;
        }
    }
    return 0;
}

//最初の画面
void start(){
    printf("\nようこそ タロットカードの世界へ\n");
    printf("=============================================\n");
    printf("皆さん初めまして、\n");
    printf("\tタロットカードといいう占い方は知っていますか。\n");
    printf("\tタロットカードは決断する時サポートするデッキです。\n");
    printf("\t今回は三つの種類のテストを準備しました。\n");
    printf("\tゆっくり遊んでください！\n");
    printf("=============================================\n\n");
    printf("------------メニュー----------\n");
    printf("1：YES OR NO----とある問題は 良い OR 悪い\n");
    printf("2：今日の運勢\n");
    printf("3：過去-現在-将来----とある問題の過去-現在-将来\n");
    printf("4：カード一覧\n");
    printf("5：終了\n");
    printf("-----------数字を入力してください----------\n");
}
//各テストの定型文
void Guidance(){
    printf("心の中で問題を思い浮かべてください。\n");
    printf("＊少女祈り中\n");
    printf("任意Lucky numberを入力してください\n");
    int e;//任意キー、とりあえずなんかある
    scanf("%d",&e);
    printf("\n");
}
//カード生成（上の部分）
void cardUp(int a){
    //int aは枚数
    int i,j;
    for(i=1;i<=a;i++){
        for(j=1;j<20;j++){
            printf("-");
        }
        printf(" ");
    }
    printf("\n");
    for(i=1;i<=a;i++){
        printf("|");
        for(j=1;j<18;j++){
            printf(" ");
        }
        printf("| ");
    }
    printf("\n");
    for(i=1;i<=a;i++){
        printf("|");
        for(j=1;j<18;j++){
            printf(" ");
        }
        printf("| ");
    }
    printf("\n");
    for(i=1;i<=a;i++){
        printf("|");
        for(j=1;j<18;j++){
            printf(" ");
        }
        printf("| ");
    }
    printf("\n");
}
//カード生成（下の部分）
void cardDown(int a){
    //int aは枚数
    int i,j;
    for(i=1;i<=a;i++){
        printf("|");
        for(j=1;j<18;j++){
            printf(" ");
        }
        printf("| ");
    }
    printf("\n");
    for(i=1;i<=a;i++){
        printf("|");
        for(j=1;j<18;j++){
            printf(" ");
        }
        printf("| ");
    }
    printf("\n");
    for(i=1;i<=a;i++){
        printf("|");
        for(j=1;j<18;j++){
            printf(" ");
        }
        printf("| ");
    }
    printf("\n");
        for(i=1;i<=a;i++){
        for(j=1;j<20;j++){
            printf("-");
        }
        printf(" ");
    }
    printf("\n");
}
//1-3共通生成結果+カード生成（中間の部分）
void output(int a,int n){ 
    // a:カードの枚数　
    //n:パタン
        //1：YES OR NO (1,1)
        //2：今日の運勢 (1,2)
        //3：過去-現在-将来(3,3)
    int i,j;
    int index;//カードの番号ランダム生成関数
    cardUp(a);    
    for(i=0;i<a;i++){
        int d=0;//判断する関数
        do {
            index = rand() % 44; // カードの番号生成
            j = 0;
            for(int k=0; k<i; k++){ //チェック
                if(b[k] == index){
                    j = 1; // 重複を発見
                    break;
                }
            }
        } while(j == 1); // 重複がある 再抽選

        b[i]=index;//番号格納する
        printf("|%20s| ",card[index].name);
    }
    printf("\n");
    cardDown(a);
    switch (n){
        case 1:
            printf("[結果]%s:%s \n",card[b[0]].name,card[b[0]].decision);
            break;
        case 2:
            printf("[結果]%s:%s \n",card[b[0]].name,card[b[0]].info);
            break;
        case 3:
            printf("[結果]\n");
            printf("過去:%s:%s \n",card[b[0]].name,card[b[0]].info);
            printf("現在:%s:%s \n",card[b[1]].name,card[b[1]].info);
            printf("将来:%s:%s \n",card[b[2]].name,card[b[2]].info);
            break;
    }
}
//カード名前一覧
void view1(){
    printf("\n");
    int j;
    for(int i=0;i<44;i++){
        if(i%2==0){
            printf("%d-",j++);
            int len = strlen(card[i].name);
            int cut_len = len - 5;
            printf("%.*s\n", cut_len, card[i].name);
        }
    }
}
//カード情報見る
void view2(){
    while (1){
        printf("\nもっと詳しく、\n");
        printf("カード番号を入力してください：\n");

        if (scanf("%d", &w) != 1) {
            printf("-----------数字(0から21)を入力してください----------\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        if(w>=0 && w<=21){
            cardUp(2);
            printf("|%20s| ",card[w*2].name);
            printf("|%20s| \n",card[w*2+1].name);
            cardDown(2);
            printf("%sの意味は%s、選択肢は%s \n",card[w*2].name,card[w*2].info,card[w*2].decision);
            printf("%sの意味は%s、選択肢は%s \n",card[w*2+1].name,card[w*2+1].info,card[w*2+1].decision);
            break;
        }else{//0から21以外NG
                printf("-----------数字(0から21)を入力してください----------\n");
        }
    }
}
//モード切替
int loop(){
    printf("\n");
    printf("1:メニューに戻る\n");
    printf("2:終了\n");
    printf("-----------数字を入力してください----------\n");
    while (1){
        scanf("%d",&w);
        if(w==1 || w==2){
            return w;
        }else{//1 or 2以外NG
            printf("-----------数字(1 or 2)を入力してください----------\n");
            while (getchar() != '\n'){
                break;
            }
        }
    }
}

