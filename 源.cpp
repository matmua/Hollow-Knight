/*	程序设计基础
* @name 期末游戏作业-空洞洞骑士
* @anthor 周一班-郭腾达/代言
* @data 2021/12/15
*/

#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include<time.h>
#include<stdlib.h>
#include <math.h>

#pragma comment(lib,"Winmm.lib")

//游戏界面长和宽
#define height 780
#define width 1400

//背景图
IMAGE bk;
//砖块长和宽
#define BRICK_HEIGHT 47
#define BRICK_WIDTH 260

IMAGE firstbk;//背景
IMAGE s1rq;//1右静止
IMAGE s1rr;//1右走
IMAGE s1rp;//1右预备
IMAGE s1rb;//1右起手
IMAGE s1rf;//1右攻击
IMAGE s1rt;//1右特效
IMAGE s1lp;//1左预备
IMAGE s1lb;//1左起手
IMAGE s1lf;//1左正攻
IMAGE s1lt;//1左特效
IMAGE s1lq;//1左静止
IMAGE s1lr;//1左走
IMAGE s2lq;//2左走
IMAGE s2lb;//2左起手
IMAGE s2lf;//2左正攻
IMAGE s2lt;//2左特效
IMAGE s2rq;//2右走
IMAGE s2rb;//2右起手
IMAGE s2rf;//2右正攻
IMAGE s2rt;//2右特效
IMAGE s3lq;//3左走
IMAGE s3lb;//3左起手
IMAGE s3lf;//3左正攻
IMAGE s3lt;//3左特效
IMAGE s3rq;//3右走
IMAGE s3rb;//3右起手
IMAGE s3rf;//3右正攻
IMAGE s3rt;//3右特效
IMAGE s40q;//boss静止
IMAGE s41p;//boss瞬移预备
IMAGE s41b;//boss瞬移起手
IMAGE s41f;//boss瞬移正攻
IMAGE s41t;//boss瞬移特效
IMAGE s42lp;//boss左范围预备
IMAGE s42lb;//boss左范围起手
IMAGE s42lf;//boss左范围正攻
IMAGE s42lt;//boss左范围特效
IMAGE s42rp;//boss右范围预备
IMAGE s42rb;//boss右范围起手
IMAGE s42rf;//boss右范围正攻
IMAGE s42rt;//boss右范围特效
IMAGE s43q;//boss恢复特效
IMAGE s44q;//boss全屏动作
IMAGE s44t;//boss全屏特效
IMAGE img_strat;//初始界面
IMAGE img_bad;//坏结局
IMAGE img_happy;//好结局
IMAGE cover;//遮罩
IMAGE help;//帮助
IMAGE page0;//故事
IMAGE page1;//故事
IMAGE page2;//故事
IMAGE page3;//故事
IMAGE page4;//故事
IMAGE page5;//故事
IMAGE page6;//故事
IMAGE page7;//故事
IMAGE page8;//故事
IMAGE page9;//故事
IMAGE page10;//故事

IMAGE life;//空洞洞血量条
IMAGE life_break;//五个小怪血量条的间隔图片
IMAGE sm_life[5];//小怪血量条
IMAGE sm2_life[5];
IMAGE sm3_life[5];
IMAGE sister_life;//小姐姐血量条

struct small_monster//定义小怪
{
	int sm_x;//x位置
	int sm_y;//y位置
	float life;//生命值
	float power;//攻击力
	float v;//移动速度
	int mons1fightflag;//判断怪物1是否发起进攻
	int mons1;//怪物1攻击动作帧计数,（正右负左）
	int mons1runflag;//怪物1行进时长计数（正静止负运动）
	int flag1;//行进方向（0右1左）
};
small_monster sm[5];//第一阶段怪物
small_monster sm2[5];//第二阶段怪物
small_monster sm3[5];//第三阶段怪物
small_monster sm4;//boss
int flag_sm2 = 0;
int flag_sm3 = 0;
int flag_sm4 = 0;
//int man_x = 500;
//int man_y = 630;
int stock_x;//陨石x
int stock_y;//陨石y


//knight为主角图像，knight_x和knight_y为主角图像所在的位置——左上角点
int knight_x = 700, knight_y = 600;

//人物血量
int knight_life = 2000;

//人物图像
IMAGE knight;

//isLimit用来判断knight是否到达画框外，若到达，为0，若到达，为1
//knight_x最大值为600，最小值为0；knight_y最大值为1340，最小值为0
//isLimit与run配合使用，当isLimit为1时，将run的值归为-1
int isLimit = 0;

//i为技能时间计数变量，每启动一个技能，i归为0，每次循环逐渐加1，累加到20后技能结束；所有技能都使用i技能，这是为了避免重复使用技能
int i = 0;

//表示是否向前奔跑，-1为静止，1为奔跑。之所以使用-1和1而不是使用1和0，是因为我们可以通过“run=-run”来切换状态，仅仅使用一个键
int run = -1;

//方向，vl为1，向右；vl为-1，向左。默认为1。
//同时，vl也用作速度，即通过knight_x+=vl来实现knight的移动，为1，向右移动，为-1，向左移动
int vl = 1;

//跳跃技能，jump为1，跳跃，jump为-1，静止。jump_为跳跃时的人物图像。之所以用-1和1而不是使用1和0，是因为我们可以通过“jump=-jump来切换状态，仅仅使用一个键
int jump = 0;
IMAGE jump_;

//vr是跳跃的速度
int vr = 7;

//闪现技能
int flash = 0;
IMAGE flash_;

//技能a，killa_为技能a的图像，快速前进，拟改动
int killa = 0;
IMAGE killa_;

//技能b，killb_为技能b的图像，喷射黑色烟雾
int killb = 0;
IMAGE killb_;
#define b_kill 20

//技能c，快速前进，附带金色光环，killc_effort_为光环图像
int killc = 0;
IMAGE killc_effort;
#define c_kill 5

//技能d，黑色幽灵，技能不能重复使用；dl是黑色幽灵的方向
int killd = 0;
int d_time = 0;
IMAGE killd_effort;
int dx = 0, dy = 0;
int dl = 1;
int isD = 0;
int d_effort_time = 0;
#define d_kill 15

//技能e,该技能会发射一个紫色宝石，ex和ey是宝石的坐标，技能不能重复使用；el是紫色宝石的方向
int kille = 0;
int e_time = 0;
IMAGE kille_effort;
IMAGE kille_effort_effort;
int ex = 0, ey = 0;
int el = 1;
int isE = 0;
int e_effort_time = 0;
#define e_kill 10

//设定knight会随重力下降，每次下降gravity
int gravity = 10;

//三块砖的位置坐标
int brick1_x = 230;
int brick1_y = 433;
int brick2_x = 568;
int brick2_y = 255;
int brick3_x = 908;
int brick3_y = 433;

//这个变量用来判断空洞洞是否受到攻击，0，未受到攻击，1，受到攻击。若受到攻击，切换图片。未使用
int isAttack = 0;

//地刺，地刺会突然从地下冒出，造成伤害，大小200*200
IMAGE spike;
int spike_effort_time = 0;
int iSpike = 0;
#define spike_kill 5

//捕梦网，捕梦网会突然出现，若被捕梦网套住，无法运动，无法施展任何技能，大小200*200
IMAGE dream;
int dream_time = 0;
int isDream = 0;

//巨型毒虫，毒虫会突然出现，若与毒虫接触会中毒
IMAGE bug;
int isBug = 0;
int bug_time = 0;
int bug_x;
int bug_y;
#define bug_kill 10

//回血石，回血石会突然出现，接触回血石会回血
IMAGE stone;
int iStone = 0;
int stone_x;
int stone_y;
int stone_time = 0;
#define REBLOOD 15

//鬼手，鬼手会突然从两侧边界冒出，造成伤害，大小200*120
IMAGE ghost_left;
IMAGE ghost_right;
int isGhost = 1;
int ghost_y;
int ghost_time = 0;
#define ghost_kill 5;

//加载界面会用到的对象
IMAGE load_back;
IMAGE load_life;
IMAGE load_life_head;
int load_life_len = 0;
IMAGE load_hint;

//这个变量用于判断进入哪个show函数：
int game = 1;

//自定义函数声明：
void updateWithoutInput();
void updateWithInput();
void gameover();
//这是一个用于判断两个矩形是否相交的函数
int isCover(int x1, int x2, int y1, int y2, int a1, int a2, int b1, int b2);
//添加遮罩图函数
void putimg(int picture_x, int picture_y, IMAGE* picture);
//showload函数声明 
void showload();

//int flag1[5];//行进方向（0右1左）
//存档
//初始菜单
//游戏初始化
//地图碰撞
//怪物生成
//怪物移动
small_monster* create_monster(small_monster sm[]);//怪物1的定义

void small_monster_run(small_monster sm[]);//怪物1一般行动
void pre();//loading
void show();	 //游戏显示模块,函数4
void showm1(int i);//怪物1动作,函数5
small_monster* create_monster2(small_monster sm2[]);//怪物2定义，函数6
void small_monster_run2(int i);//怪物2一般行动，函数7
void showm2(int i);//怪物2展示，函数8
small_monster* create_monster3(small_monster sm3[]);//创建怪物3,函数9
void small_monster_run3(int i);	 //小怪3的运动,函数10
void showm3(int i);//小怪3展示，函数11
small_monster* create_monster4();//创建boss：小姐姐，函数12
void small_monster_run4();//小姐姐移动，函数13
void showm4();//小姐姐展示，函数14
void startMenu();//开始界面
void endline();//结束阶段
void help_me();//帮助函数
void story_begin();//情节展开，写在startmeau后
void happy_story();//happy end
void bad_story();//bad end
int main()
{
	initgraph(1400, 780);// 读取图片至绘图窗口
	create_monster(sm);
	create_monster2(sm2);
	create_monster3(sm3);
	create_monster4();

	pre();

	startMenu();
	showload();
	BeginBatchDraw();

	//char s[10] = "how";
	//ExMessage m;		// 定义消息变量
	mciSendString(_T("stop load_music"), NULL, 0, NULL);
	mciSendString(_T("open music\\mons1.mp3 alias mons_music"), NULL, 0, NULL);
	mciSendString(_T("play mons_music repeat"), NULL, 0, NULL);     //循环播放音乐
	while (knight_life > 0 && sm4.life > 0)
	{
		show();
		FlushBatchDraw();
		small_monster_run(sm);//小怪1移动
		updateWithInput();
		updateWithoutInput();
		Sleep(15);
	}
	EndBatchDraw();
	endline();
	_getch();

	closegraph();
	return 0;
}
small_monster* create_monster(small_monster sm[])//创建小怪,函数1
{
	srand((unsigned int)time(NULL));
	//for (int i = 0; i < 5; i++)
	//	printf("%d ", sm[i].sm_y);
	for (int i = 0; i < 5; i++)
	{
		sm[i].sm_x = rand() % (1100 + 1) + 200;//随机数200-1200
		sm[i].sm_y = 50;
		sm[i].life = 250;
		sm[i].power = 10;
		sm[i].v = 5;
		sm[i].mons1 = 0;
		sm[i].mons1fightflag = 0;
		sm[i].mons1runflag = 0;
		sm[i].flag1 = 0;
		//sm[i].mons1fightto = 0;
	}
	//for(int i=0;i<5;i++)
		//printf("%d ", sm[i].sm_y);
	return sm;
}
small_monster* create_monster2(small_monster sm2[])//创建怪物2
{
	srand((unsigned int)time(NULL));
	//for (int i = 0; i < 5; i++)
	//	printf("%d ", sm[i].sm_y);
	for (int i = 0; i < 5; i++)
	{
		sm2[i].sm_x = rand() % (1100 + 1) + 200;//随机数200-1200
		sm2[i].sm_y = 50;
		sm2[i].life = 250;
		sm2[i].power = 30;
		sm2[i].v = 10;
		sm2[i].mons1 = 0;
		sm2[i].mons1fightflag = 0;
		sm2[i].mons1runflag = 0;
		sm2[i].flag1 = 0;
		//sm[i].mons1fightto = 0;
	}
	//for(int i=0;i<5;i++)
		//printf("%d ", sm[i].sm_y);
	return sm2;
}
small_monster* create_monster3(small_monster sm3[])//创建怪物3
{
	srand((unsigned int)time(NULL));
	//for (int i = 0; i < 5; i++)
	//	printf("%d ", sm[i].sm_y);
	for (int i = 0; i < 5; i++)
	{
		sm3[i].sm_x = rand() % (1100 + 1) + 200;//随机数200-1200
		sm3[i].sm_y = rand() % (630 + 1) + 0;//随机数0-630
		sm3[i].life = 250;
		sm3[i].power = 30;
		sm3[i].v = 10;
		sm3[i].mons1 = 0;
		sm3[i].mons1fightflag = 0;
		sm3[i].mons1runflag = 0;
		sm3[i].flag1 = 0;
		//sm[i].mons1fightto = 0;
	}
	//for(int i=0;i<5;i++)
		//printf("%d ", sm[i].sm_y);
	return sm3;
}
small_monster* create_monster4()
{
	sm4.sm_x = 1100;//boss定x
	sm4.sm_y = 570;//boss落于地面
	sm4.life = 6000;
	sm4.power = 50;
	sm4.v = 10;
	sm4.mons1 = 0;
	sm4.mons1fightflag = 0;
	sm4.mons1runflag = 0;
	sm4.flag1 = 0;
	return &sm4;
}
void pre()//整体初始化，函数3
{
	loadimage(&stone, _T("空洞洞骑士\\stone.png"), 80, 100);
	loadimage(&ghost_left, _T("空洞洞骑士\\ghost_left.png"), 200, 120);
	loadimage(&ghost_right, _T("空洞洞骑士\\ghost_right.png"), 200, 120);
	loadimage(&load_life_head, _T("load\\load_life_head.png"), 15, 15);
	loadimage(&load_back, _T("load\\load_back.png"), 1400, 780);

	for (int i = 0; i < 5; i++) {
		loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
	}
	for (int i = 0; i < 5; i++) {
		loadimage(&sm2_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
	}
	for (int i = 0; i < 5; i++) {
		loadimage(&sm3_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
	}


	loadimage(&knight, _T("right\\knight1.png"), 60, 60);
	loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
	loadimage(&life_break, _T("right\\break.png"), 10, 10);

	loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);

	loadimage(&spike, _T("空洞洞骑士\\spike.png"), 300, 100);
	loadimage(&dream, _T("空洞洞骑士\\dream1.png"), 200, 200);

	loadimage(&firstbk, _T("空洞洞骑士\\空洞洞骑士地图.png"), 1400, 780);
	loadimage(&img_strat, _T("空洞洞骑士\\初始界面.png"), 1400, 780);
	loadimage(&img_happy, _T("空洞洞骑士\\happy_end.png"), 1400, 780);
	loadimage(&img_bad, _T("空洞洞骑士\\bad_end.png"), 1400, 780);
	loadimage(&help, _T("空洞洞骑士\\帮助.png"), 1400, 780);
	loadimage(&page0, _T("空洞洞骑士\\故事page0.png"), 1400, 780);
	loadimage(&page1, _T("空洞洞骑士\\故事page1.png"), 1400, 780);
	loadimage(&page2, _T("空洞洞骑士\\故事page2.png"), 1400, 780);
	loadimage(&page3, _T("空洞洞骑士\\故事page3.png"), 1400, 780);
	loadimage(&page4, _T("空洞洞骑士\\故事page4.png"), 1400, 780);
	loadimage(&page5, _T("空洞洞骑士\\故事page5.png"), 1400, 780);
	loadimage(&page6, _T("空洞洞骑士\\故事page6.png"), 1400, 780);
	loadimage(&page7, _T("空洞洞骑士\\故事page7.png"), 1400, 780);
	loadimage(&page8, _T("空洞洞骑士\\故事page8.png"), 1400, 780);
	loadimage(&page9, _T("空洞洞骑士\\故事page9.png"), 1400, 780);
	loadimage(&page10, _T("空洞洞骑士\\故事page10.png"), 1400, 780);
	loadimage(&s1rq, _T("空洞洞骑士\\小怪1右静止正式透明.png"), 100, 100);
	loadimage(&s1rr, _T("空洞洞骑士\\小怪1行走右正式透明.png"), 100, 100);
	loadimage(&s1rp, _T("空洞洞骑士\\小怪1右预备正式透明.png"), 100, 100);
	loadimage(&s1rb, _T("空洞洞骑士\\小怪1右起手正式透明.png"), 100, 100);
	loadimage(&s1rf, _T("空洞洞骑士\\小怪1右正攻正式透明.png"), 100, 100);
	loadimage(&s1rt, _T("空洞洞骑士\\小怪1右特效正式透明.png"), 100, 100);
	loadimage(&s1lq, _T("空洞洞骑士\\小怪1左静止正式透明.png"), 100, 100);
	loadimage(&s1lr, _T("空洞洞骑士\\小怪1左行走正式透明.png"), 100, 100);
	loadimage(&s1lp, _T("空洞洞骑士\\小怪1左预备正式透明.png"), 100, 100);
	loadimage(&s1lb, _T("空洞洞骑士\\小怪1左起手正式透明.png"), 100, 100);
	loadimage(&s1lf, _T("空洞洞骑士\\小怪1左正攻正式透明.png"), 100, 100);
	loadimage(&s1lt, _T("空洞洞骑士\\小怪1左特效正式透明.png"), 100, 100);
	loadimage(&s2lq, _T("空洞洞骑士\\小怪2左行走正式透明.png"), 75, 75);
	loadimage(&s2lb, _T("空洞洞骑士\\小怪2左起手正式透明.png"), 75, 75);
	loadimage(&s2lf, _T("空洞洞骑士\\小怪2左正攻正式透明.png"), 75, 75);
	loadimage(&s2lt, _T("空洞洞骑士\\小怪2左特效正式透明.png"), 75, 75);
	loadimage(&s2rq, _T("空洞洞骑士\\小怪2右行走正式透明.png"), 75, 75);
	loadimage(&s2rb, _T("空洞洞骑士\\小怪2右起手正式透明.png"), 75, 75);
	loadimage(&s2rf, _T("空洞洞骑士\\小怪2右正攻正式透明.png"), 75, 75);
	loadimage(&s2rt, _T("空洞洞骑士\\小怪2右特效正式透明.png"), 75, 75);
	loadimage(&s3lq, _T("空洞洞骑士\\小怪3左行动正式透明.png"), 60, 60);
	loadimage(&s3lb, _T("空洞洞骑士\\小怪3左起手正式透明.png"), 60, 60);
	loadimage(&s3lf, _T("空洞洞骑士\\小怪3左正攻正式透明.png"), 60, 60);
	loadimage(&s3lt, _T("空洞洞骑士\\小怪3左特效正式透明.png"), 60, 60);
	loadimage(&s3rq, _T("空洞洞骑士\\小怪3右行动正式透明.png"), 60, 60);
	loadimage(&s3rb, _T("空洞洞骑士\\小怪3右起手正式透明.png"), 60, 60);
	loadimage(&s3rf, _T("空洞洞骑士\\小怪3右正攻正式透明.png"), 60, 60);
	loadimage(&s3rt, _T("空洞洞骑士\\小怪3右特效正式透明.png"), 60, 60);
	loadimage(&s40q, _T("空洞洞骑士\\boss静止.png"), 100, 100);
	loadimage(&s41p, _T("空洞洞骑士\\boss瞬移预备.png"), 100, 100);
	loadimage(&s41b, _T("空洞洞骑士\\boss瞬移起手.png"), 100, 100);
	loadimage(&s41f, _T("空洞洞骑士\\boss瞬移正攻.png"), 100, 100);
	loadimage(&s41t, _T("空洞洞骑士\\boss瞬移特效.png"), 300, 160);
	loadimage(&s42lp, _T("空洞洞骑士\\boss左范围预备.png"), 100, 100);
	loadimage(&s42lb, _T("空洞洞骑士\\boss左范围起手.png"), 100, 100);
	loadimage(&s42lf, _T("空洞洞骑士\\boss左范围正攻.png"), 100, 100);
	loadimage(&s42lt, _T("空洞洞骑士\\boss左范围特效.png"), 500, 100);
	loadimage(&s42rp, _T("空洞洞骑士\\boss右范围预备.png"), 100, 100);
	loadimage(&s42rb, _T("空洞洞骑士\\boss右范围起手.png"), 100, 100);
	loadimage(&s42rf, _T("空洞洞骑士\\boss右范围正攻.png"), 100, 100);
	loadimage(&s42rt, _T("空洞洞骑士\\boss右范围特效.png"), 500, 100);
	loadimage(&s43q, _T("空洞洞骑士\\boss恢复.png"), 100, 100);
	loadimage(&s44q, _T("空洞洞骑士\\boss全屏动作.png"), 100, 100);
	loadimage(&s44t, _T("空洞洞骑士\\boss全屏特效.png"), 225, 225);
}
void show()	 //游戏显示模块,函数4
{
	putimg(0, 0, &firstbk);//展示地图
	putimage(0, 0, &life);//展示骑士血量条

	srand((unsigned int)time(NULL));

	//地刺输出：
	if ((iSpike == 1) && (knight_y == 600)) {
		putimg(knight_x - 120, knight_y + 20, &spike);
	}
	//捕梦网输出：
	if (isDream == 1) {
		putimg(knight_x - 70, knight_y - 70, &dream);
	}
	//毒虫输出：
	if (isBug == 1) {
		/*bug_x = rand() % 1200;
		bug_y = rand() % 250;*/
		putimg(bug_x, bug_y, &bug);
		/*bug_x = knight_x;
		bug_y = knight_y;
		putimg(knight_x, knight_y, &bug);*/
	}
	//鬼手输出：
	if ((isGhost == 1) && ((knight_x < 60) || (knight_x > 1280))) {
		putimg(0, knight_y - 50, &ghost_left);
		putimg(1200, knight_y - 50, &ghost_right);
	}
	//回血石输出：
	if (iStone == 1) {
		putimg(stone_x, stone_y, &stone);
	}
	//怪物：
	for (int i = 0; i < 5; i++)//怪物的动作展示
	{
		if (sm[i].life > 0)
			showm1(i);

		if (sm2[i].life > 0 && sm[0].life <= 0
			&& sm[1].life <= 0 && sm[2].life <= 0
			&& sm[3].life <= 0 && sm[4].life <= 0)
		{
			if (flag_sm2 == 0)
			{
				flag_sm2 = 1;
				for (int j = 0; j < 5; j++)
					sm2[j].life = 150;
			}
			sm2[i].flag1 = rand() % (1 + 1) + 0;
			small_monster_run2(i);
			showm2(i);
		}
		if (sm3[i].life > 0 && sm2[0].life <= 0
			&& sm2[1].life <= 0 && sm2[2].life <= 0
			&& sm2[3].life <= 0 && sm2[4].life <= 0)
		{
			if (flag_sm3 == 0)
			{
				flag_sm3 = 1;
				for (int j = 0; j < 5; j++)
					sm3[j].life = 300;
			}
			sm3[i].flag1 = rand() % (1 + 1) + 0;
			small_monster_run3(i);//小怪3移动
			showm3(i);
		}
		if (sm4.life > 0 && sm3[0].life <= 0
			&& sm3[1].life <= 0 && sm3[2].life <= 0
			&& sm3[3].life <= 0 && sm3[4].life <= 0)
		{
			if (flag_sm4 == 0)
			{
				flag_sm4 = 1;
				mciSendString(_T("stop mons_music"), NULL, 0, NULL);
				mciSendString(_T("open music\\boss1.mp3 alias boss_music"), NULL, 0, NULL);
				mciSendString(_T("play boss_music repeat"), NULL, 0, NULL);     //循环播放音乐
				for (int j = 0; j < 5; j++)
					sm4.life = 6000;
			}
			if (sm4.flag1 == 0)
			{
				sm4.flag1 = rand() % (100 + 1) + 1;//对于小姐姐而言，flag1为技能选取
				small_monster_run4();
			}
			showm4();
			////下面这个语句用来录入小姐姐的血量
			//loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
			////下面这个语句用来输出小姐姐的血量
			//putimage(0, 10, &sister_life);
			//putimage(0, 10, &life_break);


		}
	}

	//主角技能输出：
	if (vl == 1) {
		//跳跃输出：
		if (jump == 1) {
			putimg(knight_x, knight_y, &knight);
			knight_y -= vr;
		}
		else {
			putimg(knight_x, knight_y, &knight);
		}
		//killa输出：
		if (killa == 1) {
			putimg(knight_x, knight_y, &knight);
			knight_x += 5;
		}
		//killb输出：
		if (killb == 1) {
			putimg(knight_x + 60, knight_y, &killb_);
		}
		//killc输出：
		if (killc == 1) {
			putimg(knight_x - 30, knight_y - 30, &killc_effort);
		}
		//killd输出：
		if (killd == 1) {
			putimg(knight_x, knight_y, &knight);
		}
		//kille输出：
		if (kille == 1) {
			putimg(knight_x, knight_y, &knight);
			putimg(knight_x + 60, knight_y, &kille_effort_effort);
		}
	}
	else {
		//跳跃输出：
		if (jump == 1) {
			putimg(knight_x, knight_y, &knight);
			knight_y -= vr;
		}
		else {
			putimg(knight_x, knight_y, &knight);
		}
		//killa输出：
		if (killa == 1) {
			putimg(knight_x, knight_y, &knight);
			knight_x -= 5;
		}
		//killb输出：
		if (killb == 1) {
			putimg(knight_x - 60, knight_y, &killb_);
		}
		//killc输出：
		if (killc == 1) {
			putimg(knight_x - 30, knight_y - 30, &killc_effort);
		}
		//killd输出：
		if (killd == 1) {
			putimg(knight_x, knight_y, &knight);
		}
		//kille输出：
		if (kille == 1) {
			putimg(knight_x, knight_y, &knight);
			putimg(knight_x - 60, knight_y, &kille_effort_effort);
		}

	}
	//killd子弹输出：
	if (isD == 1) {
		putimg(dx, dy, &killd_effort);
	}
	//kille子弹输出：
	if (isE == 1) {
		putimg(ex, ey, &kille_effort);
	}
}
void small_monster_run(small_monster sm[])	 //小怪1的运动，函数2
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 5; i++)
	{
		sm[i].flag1 = rand() % (1 + 1) + 0;
		if (sm[i].life > 0)
		{
			if ((sm[i].sm_y < 580) && ((sm[i].sm_y != 165 && sm[i].sm_y != 335)
				|| (sm[i].sm_y == 165 && (sm[i].sm_x < 508 || sm[i].sm_x > 798))
				|| (sm[i].sm_y == 335 && ((sm[i].sm_x < 190 || sm[i].sm_x > 450) &&
					(sm[i].sm_x < 878 || sm[i].sm_x > 1118)))))
				sm[i].sm_y += 5;
			else if (sm[i].flag1 == 0)
			{
				sm[i].sm_x += 1;//flag为0右
			}
			else
			{
				sm[i].sm_x -= 1;//为1左
			}
		}
	}

}
void showm1(int i)
{
	game = 1;

	//小怪血量条：
	putimage(0, 10, &life_break);
	putimage(10, 10, &sm_life[0]);
	putimage(280, 10, &life_break);
	putimage(290, 10, &sm_life[1]);
	putimage(560, 10, &life_break);
	putimage(570, 10, &sm_life[2]);
	putimage(840, 10, &life_break);
	putimage(850, 10, &sm_life[3]);
	putimage(1120, 10, &life_break);
	putimage(1130, 10, &sm_life[4]);




	if (knight_x > sm[i].sm_x && knight_x <= sm[i].sm_x + 200 && sm[i].mons1fightflag == 0
		&& knight_y >= sm[i].sm_y && knight_y < sm[i].sm_y + 100)
		sm[i].mons1fightflag = 1;//右攻击判断开始运行
	else if (knight_x < sm[i].sm_x && knight_x >= sm[i].sm_x - 200 && sm[i].mons1fightflag == 0
		&& knight_y > sm[i].sm_y && knight_y <= sm[i].sm_y + 100)
		sm[i].mons1fightflag = -1;//左攻击判断开始运行


	//右攻击
	if (sm[i].mons1fightflag > 0)//yes
	{
		if (sm[i].mons1 < 10)//预备
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rp);
			sm[i].mons1++;
		}
		else if (sm[i].mons1 < 20)//起手
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rb);
			sm[i].mons1++;
		}
		else//击打
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rf);
			putimg(sm[i].sm_x + 50, sm[i].sm_y, &s1rt);
			sm[i].mons1++;//25帧掉血
			if (sm[i].mons1 == 25 && knight_x > sm[i].sm_x && knight_x <= sm[i].sm_x + 200
				&& knight_y >= sm[i].sm_y && knight_y < sm[i].sm_y + 100) {
				knight_life -= 30;//主角掉血
				loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			}

			if (sm[i].mons1 == 30)
			{
				sm[i].mons1fightflag = 0;
				sm[i].mons1 = 0;
			}
		}
	}

	//左攻击
	if (sm[i].mons1fightflag < 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;
		if (sm[i].mons1 > -10)//预备
		{
			//putimg(sm[i].sm_x, sm[i].sm_y, &cover);
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lp);
			sm[i].mons1--;
		}
		else if (sm[i].mons1 > -20)//起手
		{
			//putimg(sm[i].sm_x, sm[i].sm_y, &cover);
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lb);
			sm[i].mons1--;
		}
		else// if (a.mons1 > -30)//击打
		{
			//putimg(sm[i].sm_x, sm[i].sm_y, &cover);
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lf);
			//putimg(sm[i].sm_x, sm[i].sm_y, &cover);
			putimg(sm[i].sm_x - 50, sm[i].sm_y, &s1lt);
			sm[i].mons1--;
			if (sm[i].mons1 == -25 && knight_x < sm[i].sm_x && knight_x >= sm[i].sm_x - 200
				&& knight_y > sm[i].sm_y && knight_y <= sm[i].sm_y + 100) {
				knight_life -= 30;//主角掉血
				loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			}
			if (sm[i].mons1 == -30)
			{
				sm[i].mons1fightflag = 0;
				sm[i].mons1 = 0;
			}
		}
	}

	//移动
	if (sm[i].mons1fightflag == 0)
	{
		if (sm[i].flag1 == 0 && sm[i].mons1runflag >= 0)//右静止
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rq);
			sm[i].mons1runflag++;
			if (sm[i].mons1runflag == 10)
				sm[i].mons1runflag = -1;
		}
		else if (sm[i].flag1 == 0 && sm[i].mons1runflag < 0)//右行走
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rr);
			sm[i].mons1runflag--;
			if (sm[i].mons1runflag == -10)
				sm[i].mons1runflag = 1;
		}
		else if (sm[i].flag1 == 1 && sm[i].mons1runflag >= 0)//左静止
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lq);
			sm[i].mons1runflag++;
			if (sm[i].mons1runflag == 10)
				sm[i].mons1runflag = -1;
		}
		else//左行走
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lr);
			sm[i].mons1runflag--;
			if (sm[i].mons1runflag == -10)
				sm[i].mons1runflag = 1;
		}
	}
	//sm[i].life -= 10;
}
void small_monster_run2(int i)	 //小怪2的运动，函数2
{
	if (sm2[i].life > 0)
	{
		if ((sm2[i].sm_y < 605) && ((sm2[i].sm_y != 190 && sm2[i].sm_y != 365)
			|| (sm2[i].sm_y == 190 && (sm2[i].sm_x < 508 || sm2[i].sm_x > 818))
			|| (sm2[i].sm_y == 365 && ((sm2[i].sm_x < 190 || sm2[i].sm_x > 450) &&
				(sm2[i].sm_x < 878 || sm2[i].sm_x > 1138)))))
			sm2[i].sm_y += 5;
		else if (sm2[i].flag1 == 0)
		{
			sm2[i].sm_x += 2;//flag为0右
		}
		else
		{
			sm2[i].sm_x -= 2;//为1左
		}
	}

}
void showm2(int i)//怪物2的输出
{
	game = 2;

	putimage(0, 10, &life_break);
	putimage(10, 10, &sm2_life[0]);
	putimage(280, 10, &life_break);
	putimage(290, 10, &sm2_life[1]);
	putimage(560, 10, &life_break);
	putimage(570, 10, &sm2_life[2]);
	putimage(840, 10, &life_break);
	putimage(850, 10, &sm2_life[3]);
	putimage(1120, 10, &life_break);
	putimage(1130, 10, &sm2_life[4]);




	if (knight_x > sm2[i].sm_x && knight_x <= sm2[i].sm_x + 200 && sm2[i].mons1fightflag == 0
		&& knight_y > sm2[i].sm_y - 100 && knight_y <= sm2[i].sm_y + 100)
		sm2[i].mons1fightflag = 1;//右攻击判断开始运行
	else if (knight_x < sm2[i].sm_x && knight_x >= sm2[i].sm_x - 100 && sm2[i].mons1fightflag == 0
		&& knight_y > sm2[i].sm_y - 100 && knight_y <= sm2[i].sm_y + 100)
		sm2[i].mons1fightflag = -1;
	//if(sm2[i].sm_y==605&&sm2[i].mons1fightflag==0)
	//	sm2[i].mons1fightflag = 1;
	//右攻击
	//if(在右且为0)//判断人物是否在攻击范围内
	//mons1fightflag = 1;
	if (sm2[i].mons1fightflag > 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;

		if (sm2[i].mons1 < 10)//起手
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2rb);
			sm2[i].mons1++;
		}
		else// if (a.mons1 < 30)//击打
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2rf);
			//putimg(sm2[i].sm_x + 100, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x + 100, sm2[i].sm_y, &s2rt);
			sm2[i].mons1++;
			if (sm2[i].mons1 == 15 && knight_x > sm2[i].sm_x && knight_x <= sm2[i].sm_x + 200
				&& knight_y >= sm2[i].sm_y - 50 && knight_y < sm2[i].sm_y + 100) {
				knight_life -= 40;
				loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			}

			//printf("%d\n", sm2[i].mons1);
			if (sm2[i].mons1 == 20)
			{
				sm2[i].mons1fightflag = 0;
				sm2[i].mons1 = 0;
			}
		}
	}//

	//左攻击
	//if(在左且为0)//判断人物是否在攻击范围内
	//mons1fightflag = 1;
	if (sm2[i].mons1fightflag < 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;
		if (sm2[i].mons1 > -10)//起手
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2lb);
			sm2[i].mons1--;
		}
		else// if (a.mons1 > -30)//击打
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2lf);
			//putimg(sm2[i].sm_x - 100, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x - 100, sm2[i].sm_y, &s2lt);
			sm2[i].mons1--;
			if (sm2[i].mons1 == -15 && knight_x < sm2[i].sm_x && knight_x >= sm2[i].sm_x - 200
				&& knight_y > sm2[i].sm_y - 100 && knight_y <= sm2[i].sm_y + 100) {
				knight_life -= 40;
				loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			}

			//printf("%d\n", sm2[i].mons1);
			if (sm2[i].mons1 == -20)
			{
				sm2[i].mons1fightflag = 0;
				sm2[i].mons1 = 0;
			}
		}
	}


	//移动
	if (sm2[i].mons1fightflag == 0)
	{
		if (sm2[i].flag1 == 0)//右静止
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2rq);
		}
		else if (sm2[i].flag1 == 1)//左静止
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2lq);
		}
	}
	//sm2[i].life -= 10;
}
void small_monster_run3(int i)	 //小怪3的运动
{
	//srand((unsigned int)time(NULL));
	//	sm3[i].flag1 = rand() % (1 + 1) + 0;
	if (sm3[i].life > 0)
	{
		if (sm3[i].flag1 == 0 && knight_x > sm3[i].sm_x)//x趋近,朝右
		{
			sm3[i].sm_x += 2;//flag为0右
		}
		else if (sm3[i].flag1 == 0 && knight_x < sm3[i].sm_x)//x趋近，朝左
		{
			sm3[i].sm_x -= 2;//为0x左
		}
		else if (sm3[i].flag1 == 1 && knight_y > sm3[i].sm_y)//y趋近，朝上
		{
			sm3[i].sm_y += 2;//为1y上
		}
		else if (sm3[i].flag1 == 1 && knight_y < sm3[i].sm_y)
		{
			sm3[i].sm_y -= 2;//为1y下
		}
	}

}
void showm3(int i)//怪物2的输出
{
	game = 3;

	putimage(0, 10, &life_break);
	putimage(10, 10, &sm3_life[0]);
	putimage(280, 10, &life_break);
	putimage(290, 10, &sm3_life[1]);
	putimage(560, 10, &life_break);
	putimage(570, 10, &sm3_life[2]);
	putimage(840, 10, &life_break);
	putimage(850, 10, &sm3_life[3]);
	putimage(1120, 10, &life_break);
	putimage(1130, 10, &sm3_life[4]);




	if (knight_x > sm3[i].sm_x && knight_x <= sm3[i].sm_x + 100 && sm3[i].mons1fightflag == 0
		&& knight_y > sm3[i].sm_y - 100 && knight_y <= sm3[i].sm_y + 100)
		sm3[i].mons1fightflag = 1;//右攻击判断开始运行
	else if (knight_x < sm3[i].sm_x && knight_x >= sm3[i].sm_x - 100 && sm3[i].mons1fightflag == 0
		&& knight_y > sm3[i].sm_y - 100 && knight_y <= sm3[i].sm_y + 100)
		sm3[i].mons1fightflag = -1;
	//if(sm3[i].sm_y==630&&sm3[i].mons1fightflag==0)
	//	sm3[i].mons1fightflag = 1;
	//右攻击
	//if(在右且为0)//判断人物是否在攻击范围内
	//mons1fightflag = 1;
	if (sm3[i].mons1fightflag > 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;

		if (sm3[i].mons1 < 10)//起手
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3rb);
			sm3[i].mons1++;
		}
		else// if (a.mons1 < 30)//击打
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3rf);
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x + 50, sm3[i].sm_y, &s3rt);
			sm3[i].mons1++;
			if (sm3[i].mons1 == 15 && knight_x > sm3[i].sm_x && knight_x <= sm3[i].sm_x + 200
				&& knight_y >= sm3[i].sm_y - 50 && knight_y < sm3[i].sm_y + 100) {
				knight_life -= 50;
				loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			}

			if (sm3[i].mons1 == 20)
			{
				sm3[i].mons1fightflag = 0;
				sm3[i].mons1 = 0;
			}
		}
	}//

	//左攻击
	//if(在左且为0)//判断人物是否在攻击范围内
	//mons1fightflag = 1;
	if (sm3[i].mons1fightflag < 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;
		if (sm3[i].mons1 > -10)//起手
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3lb);
			sm3[i].mons1--;
		}
		else// if (a.mons1 > -30)//击打
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3lf);
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x - 50, sm3[i].sm_y, &s3lt);
			sm3[i].mons1--;
			if (sm3[i].mons1 == -15 && knight_x < sm3[i].sm_x && knight_x >= sm3[i].sm_x - 200
				&& knight_y > sm3[i].sm_y - 100 && knight_y <= sm3[i].sm_y + 100) {
				knight_life -= 50;
				loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			}

			if (sm3[i].mons1 == -20)
			{
				sm3[i].mons1fightflag = 0;
				sm3[i].mons1 = 0;
			}
		}
	}


	//移动
	if (sm3[i].mons1fightflag == 0)
	{
		if (knight_x >= sm3[i].sm_x)//右静止
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3rq);
		}
		else//左静止
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3lq);
		}
	}
	//sm3[i].life -= 10;
}
void small_monster_run4()
{
	if (sm4.flag1 > 0)
	{
		if (sm4.flag1 < 50)//普通范围攻击
		{
			;
		}
		else if (sm4.flag1 < 80)//瞬移攻击
		{
			//sm4.sm_x = knight_x;
			//sm4.sm_y = knight_y - 50;
		}
		else if (sm4.flag1 < 90)//治愈
		{
			sm4.sm_x = 1100;
			sm4.sm_y = 200;
		}
		else//全屏
		{
			sm4.sm_x = 1100;
			sm4.sm_y = 200;
		}
	}
}
void showm4()
{
	game = 4;


	putimage(0, 10, &sister_life);
	putimage(0, 10, &life_break);

	srand((unsigned int)time(NULL));
	if (sm4.flag1 > 0)
	{
		if (sm4.flag1 < 40)//普通范围攻击
		{
			if (sm4.mons1 == 0 && knight_x <= sm4.sm_x)
				sm4.mons1fightflag = 1;//左攻击
			else if (sm4.mons1 == 0 && knight_x > sm4.sm_x)
				sm4.mons1fightflag = -1;//右攻击
			if (sm4.mons1fightflag > 0)//左朝向
			{
				if (sm4.mons1 < 120)//左预备
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42lp);
					sm4.mons1++;
				}
				else if (sm4.mons1 < 160)//左起手
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42lb);
					sm4.mons1++;
				}
				else if (sm4.mons1 < 200)//左正攻
				{
					putimg(sm4.sm_x, sm4.sm_y, &s42lf);
					putimg(sm4.sm_x - 600, sm4.sm_y, &s42lt);
					sm4.mons1++;
					if (sm4.mons1 == 180 && knight_x<sm4.sm_x + 60 && knight_x>sm4.sm_x - 600
						&& knight_y >= sm4.sm_y - 100 && knight_y <= sm4.sm_y + 150) {
						knight_life -= 50;//
						loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
					}
				}
				else if (sm4.mons1 < 600)
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s40q);
					sm4.mons1++;
				}
				if (sm4.mons1 >= 600)
				{
					sm4.flag1 = 0;
					sm4.mons1fightflag = 0;
					sm4.mons1 = 0;
					sm4.sm_x = rand() % (1200 + 1) + 100;
					sm4.sm_y = rand() % (380 + 1) + 200;
				}
			}
			if (sm4.mons1fightflag < 0)//右朝向
			{
				if (sm4.mons1 > -120)//右预备
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42rp);
					sm4.mons1--;
				}
				else if (sm4.mons1 > -160)//右起手
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42rb);
					sm4.mons1--;
				}
				else if (sm4.mons1 > -200)//右正攻
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42rf);
					//putimg(sm4.sm_x + 100, sm4.sm_y, &cover);
					putimg(sm4.sm_x + 100, sm4.sm_y, &s42rt);
					sm4.mons1--;
					if (sm4.mons1 == -180 && knight_x > sm4.sm_x - 60 && knight_x < sm4.sm_x + 600
						&& knight_y >= sm4.sm_y - 100 && knight_y <= sm4.sm_y + 150) {
						knight_life -= 50;
						loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
					}

				}
				else if (sm4.mons1 > -600)
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s40q);
					sm4.mons1--;
				}
				else if (sm4.mons1 <= -600)
				{
					sm4.flag1 = 0;
					sm4.mons1fightflag = 0;
					sm4.mons1 = 0;
					sm4.sm_x = rand() % (1200 + 1) + 100;
					sm4.sm_y = rand() % (380 + 1) + 200;
				}
			}
		}
		else if (sm4.flag1 < 80)//瞬移攻击
		{
			if (sm4.mons1 == 0)//瞬移
			{
				//sm4.sm_x = knight_x;
				//sm4.sm_y = knight_y + 50;
				sm4.mons1++;
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s41p);
			}
			else if (sm4.mons1 < 120)//预备
			{
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s41p);
				sm4.mons1++;
				if (sm4.sm_y >= 5)
					sm4.sm_y -= 3;
			}
			else if (sm4.mons1 < 160)//起手
			{
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s41b);
				sm4.mons1++;
				if (sm4.mons1 == 121)
				{
					sm4.sm_x = knight_x;
					sm4.sm_y = knight_y - 100;
				}
			}
			else if (sm4.mons1 < 200)//正攻
			{
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s41f);
				//putimg(sm4.sm_x, sm4.sm_y + 100, &cover);
				putimg(sm4.sm_x - 100, sm4.sm_y + 100, &s41t);
				sm4.mons1++;
				if (sm4.mons1 == 180 && knight_x > sm4.sm_x - 100 && knight_x < sm4.sm_x + 160
					&& knight_y >= sm4.sm_y && knight_y <= sm4.sm_y + 250) {
					knight_life -= 60;
					loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
				}

			}
			else if (sm4.mons1 < 600)
			{
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s40q);
				sm4.mons1++;
			}
			else if (sm4.mons1 >= 600)
			{
				sm4.flag1 = 0;
				sm4.mons1fightflag = 0;
				sm4.mons1 = 0;
			}
		}
		else if (sm4.flag1 < 90)//治愈
		{
			//putimg(sm4.sm_x, sm4.sm_y, &cover);
			putimg(sm4.sm_x, sm4.sm_y, &s40q);
			//putimg(sm4.sm_x, sm4.sm_y - 50, &cover);
			putimg(sm4.sm_x, sm4.sm_y - 50, &s43q);
			sm4.mons1++;
			sm4.life++;//共600血
			if (sm4.mons1 == 600)
			{
				sm4.flag1 = 0;
				sm4.mons1fightflag = 0;
				sm4.mons1 = 0;
				sm4.sm_x = rand() % (1200 + 1) + 100;
				sm4.sm_y = rand() % (380 + 1) + 200;
			}
		}
		else if (sm4.flag1 >= 90)//全屏
		{
			if (sm4.mons1 == 0)
			{
				sm4.mons1++;
				stock_x = rand() % (700 + 1) + 400;
				stock_y = 0;
			}
			else if (sm4.mons1 < 100)//预备
			{
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s44q);
				//putimg(stock_x, stock_y, &cover);
				putimg(stock_x, stock_y, &s44t);
				sm4.mons1++;
			}
			else if (sm4.mons1 < 200)
			{
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s44q);
				//putimg(stock_x, stock_y, &cover);
				putimg(stock_x, stock_y, &s44t);
				sm4.mons1++;
				if (stock_x >= 0)
				{
					stock_x -= 5;
					stock_y += 5;
				}
				if (knight_x >= stock_x && knight_x <= stock_x + 225
					&& knight_y <= stock_y + 225 && knight_y >= stock_y) {
					knight_life -= 20;
					loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
				}

			}
			if (sm4.mons1 >= 200)
			{
				sm4.flag1 = 0;
				sm4.mons1fightflag = 0;
				sm4.mons1 = 0;
				sm4.sm_x = rand() % (1200 + 1) + 100;
				sm4.sm_y = rand() % (380 + 1) + 200;
			}
		}
	}
}
void updateWithInput() {
	char input;
	if (_kbhit()) {
		input = _getch();

		if ((input == 'w')) {
			if (killd == 1) killd = 0;
			if (kille == 1) kille = 0;
			jump = 1;
			i = 0;
		}
		if ((input == 'd')) {
			if (killd == 1) killd = 0;
			if (kille == 1) kille = 0;
			vl = 1;
			killa = 1;
			i = 0;
			run = 1;
		}
		if ((input == 'a')) {
			if (killd == 1) killd = 0;
			if (kille == 1) kille = 0;
			vl = -1;
			killa = 1;
			i = 0;
			run = 1;
		}
		if ((input == 'v') && !(i < 20)) {
			killb = 1;
			run = -1;
			i = 0;
		}
		if ((input == 'b')) {
			killc = 1;
			run = -1;
			i = 0;
		}
		if ((input == 'n') && !killd && !kille) {
			killd = 1;
			isD = 1;
			d_effort_time = 0;
			dl = vl;
			if (vl == 1) {
				loadimage(&killd_effort, _T("right\\killd_effort1.png"), 200, 90);
				dx = knight_x + 60; dy = knight_y - 30;
			}
			else {
				loadimage(&killd_effort, _T("left\\killd_effort1.png"), 200, 90);
				dx = knight_x - 200; dy = knight_y - 30;
			}

			run = -1;
			i = 0;
		}
		if ((input == 'm') && !kille && !killd) {
			kille = 1;
			isE = 1;
			e_effort_time = 0;
			el = vl;
			if (vl == 1) {
				loadimage(&kille_effort, _T("right\\kille_effort.png"), 30, 20);
				ex = knight_x + 60; ey = knight_y + 20;
			}
			else {
				loadimage(&kille_effort, _T("left\\kille_effort.png"), 30, 20);
				ex = knight_x - 60; ey = knight_y + 20;
			}

			run = -1;
			i = 0;
		}
	}
}
void updateWithoutInput() {

	//重力下落载入（jump时无重力下落）：
	if (jump == 1) {
		knight_y += 0;
	}
	else {
		knight_y += gravity;
	}

	//边界判断：
	if (knight_y < 80) {
		isLimit = 1;
		jump = 0;
		knight_y = 81;
	}
	if (knight_x < 0) {
		isLimit = 1;
		run = -1;
		knight_x = 1;
	}
	if (knight_x > 1340) {
		isLimit = 1;
		run = -1;
		knight_x = 1339;
	}
	if (knight_y > 600) {
		isLimit = 1;
		gravity = 0;
		knight_y = 600;
	}
	else {
		gravity = 10;
	}

	//第一块砖边界判断：
	if (isCover(knight_x, knight_x + 60, knight_y, knight_y + 60, brick1_x, brick1_x + BRICK_WIDTH, brick1_y, brick1_y + BRICK_HEIGHT)) {
		isLimit = 1;
		if ((knight_x + 60 > brick1_x) && (knight_x < brick1_x) && (knight_y < brick1_y + BRICK_HEIGHT) && (knight_y + 60 > brick1_y)) {
			knight_x = brick1_x - 61;
		}
		else if ((knight_x < brick1_x + BRICK_WIDTH) && (knight_x + 60 > brick1_x + BRICK_WIDTH) && (knight_y < brick1_y + BRICK_HEIGHT) && (knight_y + 60 > brick1_y)) {
			knight_x = brick1_x + BRICK_WIDTH + 1;
		}
		else if ((knight_y + 60 > brick1_y) && (knight_y + 60 < brick1_y + BRICK_HEIGHT) && (knight_x + 60 > brick1_x) && (knight_x < brick1_x + BRICK_WIDTH)) {
			gravity = 0;
			knight_y = brick1_y - 60;
		}
		else if ((knight_y < brick1_y + BRICK_HEIGHT) && (knight_y > brick1_y) && (knight_x + 60 > brick1_x) && (knight_x < brick1_x + BRICK_WIDTH)) {
			jump = 0;
			knight_y = brick1_y + BRICK_HEIGHT + 1;
		}
	}
	//第二块砖边界判断：
	if (isCover(knight_x, knight_x + 60, knight_y, knight_y + 60, brick1_x, brick2_x + BRICK_WIDTH, brick2_y, brick2_y + BRICK_HEIGHT)) {
		isLimit = 1;
		if ((knight_x + 60 > brick2_x) && (knight_x < brick2_x) && (knight_y < brick2_y + BRICK_HEIGHT) && (knight_y + 60 > brick2_y)) {
			knight_x = brick2_x - 61;
		}
		else if ((knight_x < brick2_x + BRICK_WIDTH) && (knight_x + 60 > brick2_x + BRICK_WIDTH) && (knight_y < brick2_y + BRICK_HEIGHT) && (knight_y + 60 > brick2_y)) {
			knight_x = brick2_x + BRICK_WIDTH + 1;
		}
		else if ((knight_y + 60 > brick2_y) && (knight_y + 60 < brick2_y + BRICK_HEIGHT) && (knight_x + 60 > brick2_x) && (knight_x < brick2_x + BRICK_WIDTH)) {
			gravity = 0;
			knight_y = brick2_y - 60;
		}
		else if ((knight_y < brick2_y + BRICK_HEIGHT) && (knight_y > brick2_y) && (knight_x + 60 > brick2_x) && (knight_x < brick2_x + BRICK_WIDTH)) {
			jump = 0;
			knight_y = brick2_y + BRICK_HEIGHT + 1;
		}
	}
	//第三块砖边界判断：
	if (isCover(knight_x, knight_x + 60, knight_y, knight_y + 60, brick3_x, brick3_x + BRICK_WIDTH, brick3_y, brick3_y + BRICK_HEIGHT)) {
		isLimit = 1;
		if ((knight_x + 60 > brick3_x) && (knight_x < brick3_x) && (knight_y < brick3_y + BRICK_HEIGHT) && (knight_y + 60 > brick3_y)) {
			knight_x = brick3_x - 61;
		}
		else if ((knight_x < brick3_x + BRICK_WIDTH) && (knight_x + 60 > brick3_x + BRICK_WIDTH) && (knight_y < brick3_y + BRICK_HEIGHT) && (knight_y + 60 > brick3_y)) {
			knight_x = brick3_x + BRICK_WIDTH + 1;
		}
		else if ((knight_y + 60 > brick3_y) && (knight_y + 60 < brick3_y + BRICK_HEIGHT) && (knight_x + 60 > brick3_x) && (knight_x < brick3_x + BRICK_WIDTH)) {
			gravity = 0;
			knight_y = brick3_y - 60;
		}
		else if ((knight_y < brick3_y + BRICK_HEIGHT) && (knight_y > brick3_y) && (knight_x + 60 > brick3_x) && (knight_x < brick3_x + BRICK_WIDTH)) {
			jump = 0;
			knight_y = brick3_y + BRICK_HEIGHT + 1;
		}
	}

	//killd技能时间判断：
	if (d_effort_time == 20) {
		isD = 0;
	}
	else {
		d_effort_time++;
	}
	//kille技能时间判断：
	if (e_effort_time == 20) {
		isE = 0;
	}
	else {
		e_effort_time++;
	}

	//knight向右时，技能载入：
	if (vl == 1) {
		if (i == 20) {
			killa = 0;
			killb = 0;
			killc = 0;
			killd = 0;
			kille = 0;
			jump = 0;
			loadimage(&knight, _T("right\\knight1.png"), 60, 60);
			run = -1;
		}
		else {
			i++;
		}

		//跳跃载入：
		if (jump == 1) {
			loadimage(&knight, _T("right\\jump.png"), 60, 60);
		}
		else {
			loadimage(&knight, _T("right\\knight1.png"), 60, 60);
		}

		//奔跑（killa）载入：
		if ((killa == 1) && (run == 1)) {
			//run = 1;
			if (i < 3) {
				loadimage(&knight, _T("right\\kill_a1.png"), 60, 60);
			}
			else if (i < 5) {
				loadimage(&knight, _T("right\\kill_abreak.png"), 60, 60);
			}
			else if (i < 7) {
				loadimage(&knight, _T("right\\kill_a2.png"), 60, 60);
			}
			else if (i < 10) {
				loadimage(&knight, _T("right\\kill_abreak.png"), 60, 60);
			}
			else if (i < 12) {
				loadimage(&knight, _T("right\\kill_abreak.png"), 60, 60);
			}
			else if (i < 15) {
				loadimage(&knight, _T("right\\kill_a2.png"), 60, 60);
			}
			else if (i < 18) {
				loadimage(&knight, _T("right\\kill_abreak.png"), 60, 60);
			}
			else {
				loadimage(&knight, _T("right\\kill_a3.png"), 60, 60);
			}
		}

		//killb载入：
		if (killb == 1) {
			//killb对小怪的打击，掉血量20*20==400，注意：虽然下方代码掉血量为20，但是实际上要乘以20，因为i从0递增到19这个阶段内，都会执行减血语句
			switch (game) {
			case 1:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x + 60, knight_x + 120, knight_y, knight_y + 60, sm[i].sm_x, sm[i].sm_x + 100, sm[i].sm_y, sm[i].sm_y + 100)) {
						sm[i].life -= b_kill;
						loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x + 60, knight_x + 120, knight_y, knight_y + 60, sm2[i].sm_x, sm2[i].sm_x + 75, sm2[i].sm_y, sm2[i].sm_y + 75)) {
						sm2[i].life -= b_kill;
						loadimage(&sm2_life[i], _T("right\\green.png"), (sm2[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x + 60, knight_x + 120, knight_y, knight_y + 60, sm3[i].sm_x, sm3[i].sm_x + 60, sm3[i].sm_y, sm3[i].sm_y + 60)) {
						sm3[i].life -= b_kill;
						loadimage(&sm3_life[i], _T("right\\green.png"), (sm3[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 4:
				if (isCover(knight_x + 60, knight_x + 120, knight_y, knight_y + 60, sm4.sm_x, sm4.sm_x + 100, sm4.sm_y, sm4.sm_y + 100)) {
					sm4.life -= b_kill;
					loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
				}
				break;
			}

			loadimage(&knight, _T("right\\killb.png"), 60, 60);
			if (i < 7) {
				loadimage(&killb_, _T("right\\kill_b1.png"), 60, 60);
			}
			else if (i < 15) {
				loadimage(&killb_, _T("right\\kill_b2.png"), 60, 60);
			}
			else {
				loadimage(&killb_, _T("right\\kill_b3.png"), 60, 60);
			}

		}

		//killc载入：
		if (killc == 1) {
			loadimage(&knight, _T("right\\kill_c1.png"), 60, 60);

			switch (game) {
			case 1:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x + 120, knight_y - 60, knight_y + 120, sm[i].sm_x, sm[i].sm_x + 100, sm[i].sm_y, sm[i].sm_y + 100)) {
						sm[i].life -= c_kill;
						loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x + 120, knight_y - 60, knight_y + 120, sm2[i].sm_x, sm2[i].sm_x + 75, sm2[i].sm_y, sm2[i].sm_y + 75)) {
						sm2[i].life -= c_kill;
						loadimage(&sm2_life[i], _T("right\\green.png"), (sm2[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x + 120, knight_y - 60, knight_y + 120, sm3[i].sm_x, sm3[i].sm_x + 60, sm3[i].sm_y, sm3[i].sm_y + 60)) {
						sm3[i].life -= c_kill;
						loadimage(&sm3_life[i], _T("right\\green.png"), (sm3[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 4:
				if (isCover(knight_x - 60, knight_x + 120, knight_y - 60, knight_y + 120, sm4.sm_x, sm4.sm_x + 100, sm4.sm_y, sm4.sm_y + 100)) {
					sm4.life -= c_kill;
					loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
				}
				break;
			}

			if (i < 3) {
				loadimage(&killc_effort, _T("right\\killc_effort0.png"), 120, 120);
			}
			else if (i < 9) {
				loadimage(&killc_effort, _T("right\\killc_effort1.png"), 120, 120);
			}
			else if (i < 11) {
				loadimage(&killc_effort, _T("right\\killc_effort0.png"), 120, 120);
			}
			else if (i < 17) {
				loadimage(&killc_effort, _T("right\\killc_effort2.png"), 120, 120);
			}
			else {
				loadimage(&killc_effort, _T("right\\killc_effort0.png"), 120, 120);
			}
			knight_x += 10;
		}

		//killd人物载入：
		if (killd == 1) {
			loadimage(&knight, _T("right\\kill_d.png"), 60, 60);
		}
		//killd子弹载入：
		if (isD == 1) {
			if (dl == 1) {
				dx += 15;
			}
			else {
				dx -= 15;
			}

			switch (game) {
			case 1:
				for (int i = 0; i < 5; i++) {
					if (isCover(dx, dx + 200, dy, dy + 90, sm[i].sm_x, sm[i].sm_x + 100, sm[i].sm_y, sm[i].sm_y + 100)) {
						sm[i].life -= d_kill;
						loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 5; i++) {
					if (isCover(dx, dx + 200, dy, dy + 90, sm2[i].sm_x, sm2[i].sm_x + 75, sm2[i].sm_y, sm2[i].sm_y + 75)) {
						sm2[i].life -= d_kill;
						loadimage(&sm2_life[i], _T("right\\green.png"), (sm2[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++) {
					if (isCover(dx, dx + 200, dy, dy + 90, sm3[i].sm_x, sm3[i].sm_x + 60, sm3[i].sm_y, sm3[i].sm_y + 60)) {
						sm3[i].life -= d_kill;
						loadimage(&sm3_life[i], _T("right\\green.png"), (sm3[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 4:
				if (isCover(dx, dx + 200, dy, dy + 90, sm4.sm_x, sm4.sm_x + 100, sm4.sm_y, sm4.sm_y + 100)) {
					sm4.life -= d_kill;
					loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
				}
				break;
			}

			if (dx > 1350) {
				isD = 0;
				dx = 1200;
				d_effort_time = 20;
			}
			if (dx < 0) {
				isD = 0;
				dx = 1;
				d_effort_time = 20;
			}
		}

		//kille人物载入：
		if (kille == 1) {
			loadimage(&knight, _T("right\\kille.png"), 60, 60);
			loadimage(&kille_effort_effort, _T("right\\kille_effort_effort.png"), 60, 60);
		}
		//kille子弹载入：
		if (isE == 1) {
			if (el == 1) {
				ex += 25;
			}
			else {
				ex -= 25;
			}

			switch (game) {
			case 1:
				for (int i = 0; i < 5; i++) {
					if (isCover(ex, ex + 30, ey, ey + 20, sm[i].sm_x, sm[i].sm_x + 100, sm[i].sm_y, sm[i].sm_y + 100)) {
						sm[i].life -= e_kill;
						loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 5; i++) {
					if (isCover(ex, ex + 30, ey, ey + 20, sm2[i].sm_x, sm2[i].sm_x + 75, sm2[i].sm_y, sm2[i].sm_y + 75)) {
						sm2[i].life -= e_kill;
						loadimage(&sm2_life[i], _T("right\\green.png"), (sm2[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++) {
					if (isCover(ex, ex + 30, ey, ey + 20, sm3[i].sm_x, sm3[i].sm_x + 60, sm3[i].sm_y, sm3[i].sm_y + 60)) {
						sm3[i].life -= e_kill;
						loadimage(&sm3_life[i], _T("right\\green.png"), (sm3[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 4:
				if (isCover(ex, ex + 30, ey, ey + 20, sm4.sm_x, sm4.sm_x + 100, sm4.sm_y, sm4.sm_y + 100)) {
					sm4.life -= e_kill;
					loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
				}
				break;
			}

			if (ex > 1370) {
				isE = 0;
				ex = 1369;
				e_effort_time = 20;
			}
			if (ex < 0) {
				isE = 0;
				ex = 1;
				e_effort_time = 20;
			}
		}


	}

	//knight向左时，技能载入
	else {
		if (i == 20) {
			killa = 0;
			killb = 0;
			killc = 0;
			killd = 0;
			kille = 0;
			jump = 0;
			loadimage(&knight, _T("left\\knight1.png"), 60, 60);

			run = -1;
		}
		else {
			i++;
		}
		//跳跃载入：
		if (jump == 1) {
			loadimage(&knight, _T("left\\jump.png"), 60, 60);
		}
		else {
			loadimage(&knight, _T("left\\knight1.png"), 60, 60);
		}
		//奔跑（killa）载入：
		if ((killa == 1) && (run == 1)) {
			//run = 1;
			if (i < 3) {
				loadimage(&knight, _T("left\\kill_a1.png"), 60, 60);
			}
			else if (i < 5) {
				loadimage(&knight, _T("left\\kill_abreak.png"), 60, 60);
			}
			else if (i < 7) {
				loadimage(&knight, _T("left\\kill_a2.png"), 60, 60);
			}
			else if (i < 10) {
				loadimage(&knight, _T("left\\kill_abreak.png"), 60, 60);
			}
			else if (i < 12) {
				loadimage(&knight, _T("left\\kill_abreak.png"), 60, 60);
			}
			else if (i < 15) {
				loadimage(&knight, _T("left\\kill_a2.png"), 60, 60);
			}
			else if (i < 18) {
				loadimage(&knight, _T("left\\kill_abreak.png"), 60, 60);
			}
			else {
				loadimage(&knight, _T("left\\kill_a3.png"), 60, 60);
			}
		}
		//killb载入：
		if (killb == 1) {

			switch (game) {
			case 1:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x, knight_y, knight_y + 60, sm[i].sm_x, sm[i].sm_x + 100, sm[i].sm_y, sm[i].sm_y + 100)) {
						sm[i].life -= b_kill;
						loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x, knight_y, knight_y + 60, sm2[i].sm_x, sm2[i].sm_x + 75, sm2[i].sm_y, sm2[i].sm_y + 75)) {
						sm2[i].life -= b_kill;
						loadimage(&sm2_life[i], _T("right\\green.png"), (sm2[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x, knight_y, knight_y + 60, sm3[i].sm_x, sm3[i].sm_x + 60, sm3[i].sm_y, sm3[i].sm_y + 60)) {
						sm3[i].life -= b_kill;
						loadimage(&sm3_life[i], _T("right\\green.png"), (sm3[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 4:
				if (isCover(knight_x - 60, knight_x, knight_y, knight_y + 60, sm4.sm_x, sm4.sm_x + 100, sm4.sm_y, sm4.sm_y + 100)) {
					sm4.life -= b_kill;
					loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
				}
				break;
			}



			loadimage(&knight, _T("left\\killb.png"), 60, 60);
			if (i < 7) {
				loadimage(&killb_, _T("left\\kill_b1.png"), 60, 60);
			}
			else if (i < 15) {
				loadimage(&killb_, _T("left\\kill_b2.png"), 60, 60);
			}
			else {
				loadimage(&killb_, _T("left\\kill_b3.png"), 60, 60);
			}
		}

		//killc载入：
		if (killc == 1) {

			switch (game) {
			case 1:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x + 120, knight_y - 60, knight_y + 120, sm[i].sm_x, sm[i].sm_x + 100, sm[i].sm_y, sm[i].sm_y + 100)) {
						sm[i].life -= c_kill;
						loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x + 120, knight_y - 60, knight_y + 120, sm2[i].sm_x, sm2[i].sm_x + 75, sm2[i].sm_y, sm2[i].sm_y + 75)) {
						sm2[i].life -= c_kill;
						loadimage(&sm2_life[i], _T("right\\green.png"), (sm2[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++) {
					if (isCover(knight_x - 60, knight_x + 120, knight_y - 60, knight_y + 120, sm3[i].sm_x, sm3[i].sm_x + 60, sm3[i].sm_y, sm3[i].sm_y + 60)) {
						sm3[i].life -= c_kill;
						loadimage(&sm3_life[i], _T("right\\green.png"), (sm3[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 4:
				if (isCover(knight_x - 60, knight_x + 120, knight_y - 60, knight_y + 120, sm4.sm_x, sm4.sm_x + 100, sm4.sm_y, sm4.sm_y + 100)) {
					sm4.life -= c_kill;
					loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
				}
				break;
			}



			loadimage(&knight, _T("left\\kill_c1.png"), 60, 60);
			if (i < 3) {
				loadimage(&killc_effort, _T("right\\killc_effort0.png"), 120, 120);
			}
			else if (i < 9) {
				loadimage(&killc_effort, _T("right\\killc_effort1.png"), 120, 120);
			}
			else if (i < 11) {
				loadimage(&killc_effort, _T("right\\killc_effort0.png"), 120, 120);
			}
			else if (i < 17) {
				loadimage(&killc_effort, _T("right\\killc_effort2.png"), 120, 120);
			}
			else {
				loadimage(&killc_effort, _T("right\\killc_effort0.png"), 120, 120);
			}
			knight_x -= 10;
		}
		//killd人物载入：
		if (killd == 1) {
			loadimage(&knight, _T("left\\kill_d.png"), 60, 60);
		}
		//killd子弹载入：
		if (isD == 1) {
			if (dl == 1) {
				dx += 15;
			}
			else {
				dx -= 15;
			}

			switch (game) {
			case 1:
				for (int i = 0; i < 5; i++) {
					if (isCover(dx, dx + 200, dy, dy + 90, sm[i].sm_x, sm[i].sm_x + 100, sm[i].sm_y, sm[i].sm_y + 100)) {
						sm[i].life -= d_kill;
						loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 5; i++) {
					if (isCover(dx, dx + 200, dy, dy + 90, sm2[i].sm_x, sm2[i].sm_x + 75, sm2[i].sm_y, sm2[i].sm_y + 75)) {
						sm2[i].life -= d_kill;
						loadimage(&sm2_life[i], _T("right\\green.png"), (sm2[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++) {
					if (isCover(dx, dx + 200, dy, dy + 90, sm3[i].sm_x, sm3[i].sm_x + 60, sm3[i].sm_y, sm3[i].sm_y + 60)) {
						sm3[i].life -= d_kill;
						loadimage(&sm3_life[i], _T("right\\green.png"), (sm3[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 4:
				if (isCover(dx, dx + 200, dy, dy + 90, sm4.sm_x, sm4.sm_x + 100, sm4.sm_y, sm4.sm_y + 100)) {
					sm4.life -= d_kill;
					loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
				}
				break;
			}
			if (dx < 0) {
				isD = 0;
				dx = 1;
				d_effort_time = 20;
			}
			if (dx > 1350) {
				isD = 0;
				dx = 1200;
				d_effort_time = 20;
			}
		}

		//kille人物动作载入：
		if (kille == 1) {
			loadimage(&knight, _T("left\\kille.png"), 60, 60);
			loadimage(&kille_effort_effort, _T("left\\kille_effort_effort.png"), 60, 60);
		}
		//kille子弹载入：
		if (isE == 1) {
			if (el == 1) {
				ex += 25;
			}
			else {
				ex -= 25;
			}

			switch (game) {
			case 1:
				for (int i = 0; i < 5; i++) {
					if (isCover(ex, ex + 30, ey, ey + 20, sm[i].sm_x, sm[i].sm_x + 100, sm[i].sm_y, sm[i].sm_y + 100)) {
						sm[i].life -= e_kill;
						loadimage(&sm_life[i], _T("right\\green.png"), (sm[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 5; i++) {
					if (isCover(ex, ex + 30, ey, ey + 20, sm2[i].sm_x, sm2[i].sm_x + 75, sm2[i].sm_y, sm2[i].sm_y + 75)) {
						sm2[i].life -= e_kill;
						loadimage(&sm2_life[i], _T("right\\green.png"), (sm2[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++) {
					if (isCover(ex, ex + 30, ey, ey + 20, sm3[i].sm_x, sm3[i].sm_x + 60, sm3[i].sm_y, sm3[i].sm_y + 60)) {
						sm3[i].life -= e_kill;
						loadimage(&sm3_life[i], _T("right\\green.png"), (sm3[i].life / 250.0) * 270, 10);
					}
				}
				break;
			case 4:
				if (isCover(ex, ex + 30, ey, ey + 20, sm4.sm_x, sm4.sm_x + 100, sm4.sm_y, sm4.sm_y + 100)) {
					sm4.life -= e_kill;
					loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
				}
				break;
			}

			if (ex > 1370) {
				isE = 0;
				ex = 1369;
				e_effort_time = 20;
			}
			if (ex < 0) {
				isE = 0;
				ex = 1;
				e_effort_time = 20;
			}
		}

	}



	//捕梦网载入：
	if (isDream == 1) {
		if (dream_time % 2) {
			loadimage(&dream, _T("空洞洞骑士\\dream2.png"), 200, 200);
		}
		else {
			loadimage(&dream, _T("空洞洞骑士\\dream1.png"), 200, 200);
		}
		loadimage(&knight, _T("right\\getcatch.png"), 60, 60);
		dream_time++;
		killa = 0;
		killb = 0;
		killc = 0;
		killd = 0;
		kille = 0;
		jump = 0;
		gravity = 0;
		if (dream_time == 30) {
			isDream = 0;
			dream_time = 0;
			loadimage(&knight, _T("right\\knight1.png"), 60, 60);
		}
	}
	else {
		isDream = rand() % 10;
	}


	//地刺载入：
	if ((iSpike == 1) && (knight_y == 600)) {
		spike_effort_time++;
		killa = 0;
		killb = 0;
		killc = 0;
		killd = 0;
		kille = 0;
		jump = 0;
		knight_life -= spike_kill;
		loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
		if (spike_effort_time == 20) {
			iSpike = 0;
			spike_effort_time = 0;
		}
	}
	else {
		iSpike = rand() % 10;
	}

	//毒虫载入：
	if (isBug == 1) {
		bug_time++;
		if (isCover(knight_x, knight_x + 60, knight_y, knight_y + 60, bug_x, bug_x + 150, bug_y, bug_y + 400)) {
			knight_life -= 5;
			loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			killa = 0;
			killb = 0;
			killc = 0;
			killd = 0;
			kille = 0;
			jump = 0;
			gravity = 0;
			loadimage(&knight, _T("right\\getcatch.png"), 60, 60);
		}

		if (bug_time < 2) {
			loadimage(&bug, _T("空洞洞骑士\\bug1.png"), 150, 400);
		}
		else if (bug_time < 4) {
			loadimage(&bug, _T("空洞洞骑士\\bug2.png"), 150, 400);
		}
		else if (bug_time < 6) {
			loadimage(&bug, _T("空洞洞骑士\\bug3.png"), 150, 400);
		}
		else if (bug_time < 8) {
			loadimage(&bug, _T("空洞洞骑士\\bug4.png"), 150, 400);
		}
		else if (bug_time < 10) {
			loadimage(&bug, _T("空洞洞骑士\\bug5.png"), 150, 400);
		}
		else if (bug_time < 12) {
			loadimage(&bug, _T("空洞洞骑士\\bug6.png"), 150, 400);
		}
		else if (bug_time < 14) {
			loadimage(&bug, _T("空洞洞骑士\\bug1.png"), 150, 400);
		}
		else if (bug_time < 16) {
			loadimage(&bug, _T("空洞洞骑士\\bug2.png"), 150, 400);
		}
		else if (bug_time < 18) {
			loadimage(&bug, _T("空洞洞骑士\\bug3.png"), 150, 400);
		}
		else if (bug_time < 20) {
			loadimage(&bug, _T("空洞洞骑士\\bug4.png"), 150, 400);
		}
		else if (bug_time < 22) {
			loadimage(&bug, _T("空洞洞骑士\\bug5.png"), 150, 400);
		}
		else if (bug_time < 24) {
			loadimage(&bug, _T("空洞洞骑士\\bug6.png"), 150, 400);
		}
		else if (bug_time < 26) {
			loadimage(&bug, _T("空洞洞骑士\\bug1.png"), 150, 400);
		}
		else if (bug_time < 28) {
			loadimage(&bug, _T("空洞洞骑士\\bug2.png"), 150, 400);
		}
		else if (bug_time < 30) {
			loadimage(&bug, _T("空洞洞骑士\\bug3.png"), 150, 400);
		}
		else if (bug_time < 32) {
			loadimage(&bug, _T("空洞洞骑士\\bug4.png"), 150, 400);
		}
		else if (bug_time < 34) {
			loadimage(&bug, _T("空洞洞骑士\\bug5.png"), 150, 400);
		}
		else if (bug_time < 36) {
			loadimage(&bug, _T("空洞洞骑士\\bug6.png"), 150, 400);
		}
		else {
			isBug = 0;
			bug_time = 0;
			loadimage(&knight, _T("right\\knight1.png"), 60, 60);
		}
	}
	else {
		isBug = rand() % 10;
		bug_x = rand() % 1200;
		bug_y = rand() % 250;
	}

	//鬼手载入：
	if ((isGhost == 1) && ((knight_x < 60) || (knight_x > 1280))) {
		ghost_time++;
		killa = 0;
		killb = 0;
		killc = 0;
		killd = 0;
		kille = 0;
		jump = 0;
		knight_life -= ghost_kill;
		loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
		if (ghost_time == 20) {
			isGhost = 0;
			ghost_time = 0;
		}
	}
	else {
		isGhost = rand() % 10;
	}

	//回血石载入：
	if (iStone == 1) {
		stone_time++;
		if (isCover(knight_x, knight_x + 60, knight_y, knight_y + 60, stone_x, stone_x + 80, stone_y, stone_y + 100)) {
			knight_life += REBLOOD;
			loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			killa = 0;
			killb = 0;
			killc = 0;
			killd = 0;
			kille = 0;
			jump = 0;
			gravity = 0;
			loadimage(&knight, _T("right\\getcatch.png"), 60, 60);
		}
		if (stone_time == 60) {
			iStone = 0;
			stone_time = 0;
			loadimage(&knight, _T("right\\knight1.png"), 60, 60);
		}
	}
	else {
		iStone = rand() % 30;
		stone_x = rand() % 1200;
		stone_y = rand() % 250;
	}


	//避免空洞洞血量大于2000：
	if (knight_life > 2000) {
		knight_life = 2000;
	}
}
void gameover() {
	EndBatchDraw();
	_getch();
	closegraph();
}
int isCover(int x1, int x2, int y1, int y2, int a1, int a2, int b1, int b2) {
	int iscover = 1;
	if (x2 < a1) {
		iscover = 0;
	}
	if (x1 > a2) {
		iscover = 0;
	}
	if (y1 > b2) {
		iscover = 0;
	}
	if (y2 < b1) {
		iscover = 0;
	}
	return iscover;
}
void putimg(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标
	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}

}
void startMenu() // 初始菜单界面
{
	ExMessage m;
	putimage(0, 0, &img_strat);//显示背景
	//rectangle(1100, 105, 1305, 180);
	//rectangle(1100, 225, 1305, 300);
	//rectangle(1100, 350, 1305, 425);
	mciSendString(_T("open music\\begin1.mp3 alias begin_music"), NULL, 0, NULL);
	//open指令打开需要播放的音乐，alias后面制定了前面文件路径的别名，以后想要操作这个文件直接使用这个别名就可以了.
	//如果音乐文件和我们的debug文件夹在同一目录下，就可以像我这样不用写路径，直接音乐名。
	//如果音乐文件不是上面的情况就得写清楚路径。
	//例: D盘下的demo目录有一个叫1.MP3的文件
	//mciSendString("open demo\\1.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString(_T("play begin_music repeat"), NULL, 0, NULL);     //循环播放音乐
	while (1)
	{
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1100 && m.x < 1305 && m.y>105 && m.y < 180)) {
			story_begin();
			return;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1100 && m.x < 1305 && m.y>225 && m.y < 300)) {
			help_me();
			return;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1100 && m.x < 1305 && m.y>350 && m.y < 425)) {
			exit(0);
		}
	}
}
void endline()
{
	if (knight_life <= 0) {
		bad_story();
		putimage(0, 0, &img_bad);
	}
	else if (sm4.life <= 0) {
		happy_story();
		putimage(0, 0, &img_happy);
	}
}
void help_me()
{
	putimage(0, 0, &help);//显示背景;
	//rectangle(1130, 650, 1335, 725);
	//rectangle(1130, 505, 1335, 580);
	ExMessage m;
	while (1)
	{
		m = getmessage(EM_MOUSE);//_getch();// Press any key to continue
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			putimage(0, 0, &page0);//故事
			//rectangle(1130, 650, 1335, 725);
			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			putimage(0, 0, &page1);
			break;
		}
	}
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
}
void story_begin()
{
	ExMessage m;
	putimage(0, 0, &page2);
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			putimage(0, 0, &page3);
			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			putimage(0, 0, &page4);
			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {

			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}

}
void happy_story()
{
	ExMessage m;
	putimage(0, 0, &page5);
	mciSendString(_T("stop boss_music"), NULL, 0, NULL);
	mciSendString(_T("open music\\happyend1.mp3 alias happy_music"), NULL, 0, NULL);
	mciSendString(_T("play happy_music repeat"), NULL, 0, NULL);     //循环播放音乐
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			putimage(0, 0, &page6);
			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			putimage(0, 0, &page7);
			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			putimage(0, 0, &page8);
			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			putimage(0, 0, &page9);
			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			break;
		}
		else if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			startMenu();
			return;
		}
	}
}
void bad_story()
{
	ExMessage m;
	putimage(0, 0, &page10);
	mciSendString(_T("stop boss_music"), NULL, 0, NULL);
	mciSendString(_T("open music\\badend1.mp3 alias bad_music"), NULL, 0, NULL);
	mciSendString(_T("play bad_music repeat"), NULL, 0, NULL);     //循环播放音乐
	while (1) {
		m = getmessage(EM_MOUSE);
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>650 && m.y < 725)) {
			break;
		}
	}
}
void showload() {
	int show = 0;
	IMAGE hint1;
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	BeginBatchDraw();
	while (load_life_len <= 600) {
		putimage(0, 0, &load_back);
		mciSendString(_T("stop begin_music"), NULL, 0, NULL);
		mciSendString(_T("open music\\load1.mp3 alias load_music"), NULL, 0, NULL);
		mciSendString(_T("play load_music repeat"), NULL, 0, NULL);     //循环播放音乐
		loadimage(&load_life, _T("load\\load_life.png"), load_life_len, 15);
		outtextxy(640, 650, L"*****LOADING*****");
		outtextxy(570, 675, L"*Although there is nothing to load.......*");
		putimage(400, 700, &load_life);
		putimage(load_life_len + 400, 700, &load_life_head);

		switch (show) {
		case 1:putimg(550, 300, &hint1);
			outtextxy(550, 400, L"*--------------------------当心地刺--------------------------*");
			break;
		case 2:putimg(550, 100, &load_hint);
			outtextxy(550, 400, L"*---如果你被捕梦网套住，你会动弹不得---*");
			break;
		case 3:putimg(625, 100, &load_hint);
			outtextxy(550, 400, L"*-----------------当心毒虫，它随时出现-----------------*");
			break;
		case 4:putimg(600, 200, &load_hint);
			outtextxy(550, 400, L"*-----------不要靠近边界，有鬼手出没-----------*");
			break;
		case 5:putimg(660, 250, &load_hint);
			outtextxy(550, 400, L"*----------这块金灿灿的石头能让你回血----------*");
			break;
		}
		FlushBatchDraw();
		if (load_life_len < 120) {
			loadimage(&hint1, _T("空洞洞骑士\\spike.png"), 300, 100);
			show = 1;
			Sleep(10);
		}
		else if (load_life_len < 240) {
			loadimage(&load_hint, _T("空洞洞骑士\\dream1.png"), 300, 300);
			show = 2;
			Sleep(10);
		}
		else if (load_life_len < 360) {
			loadimage(&load_hint, _T("空洞洞骑士\\bug1.png"), 150, 400);
			show = 3;
			Sleep(10);
		}
		else if (load_life_len < 480) {
			loadimage(&load_hint, _T("空洞洞骑士\\ghost_right.png"), 200, 120);
			show = 4;
			Sleep(10);
		}
		else {
			loadimage(&load_hint, _T("空洞洞骑士\\stone.png"), 80, 100);
			show = 5;
			Sleep(10);
		}
		load_life_len += 1;
	}
	EndBatchDraw();

}