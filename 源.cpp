/*	������ƻ���
* @name ��ĩ��Ϸ��ҵ-�ն�����ʿ
* @anthor ��һ��-���ڴ�/����
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

//��Ϸ���泤�Ϳ�
#define height 780
#define width 1400

//����ͼ
IMAGE bk;
//ש�鳤�Ϳ�
#define BRICK_HEIGHT 47
#define BRICK_WIDTH 260

IMAGE firstbk;//����
IMAGE s1rq;//1�Ҿ�ֹ
IMAGE s1rr;//1����
IMAGE s1rp;//1��Ԥ��
IMAGE s1rb;//1������
IMAGE s1rf;//1�ҹ���
IMAGE s1rt;//1����Ч
IMAGE s1lp;//1��Ԥ��
IMAGE s1lb;//1������
IMAGE s1lf;//1������
IMAGE s1lt;//1����Ч
IMAGE s1lq;//1��ֹ
IMAGE s1lr;//1����
IMAGE s2lq;//2����
IMAGE s2lb;//2������
IMAGE s2lf;//2������
IMAGE s2lt;//2����Ч
IMAGE s2rq;//2����
IMAGE s2rb;//2������
IMAGE s2rf;//2������
IMAGE s2rt;//2����Ч
IMAGE s3lq;//3����
IMAGE s3lb;//3������
IMAGE s3lf;//3������
IMAGE s3lt;//3����Ч
IMAGE s3rq;//3����
IMAGE s3rb;//3������
IMAGE s3rf;//3������
IMAGE s3rt;//3����Ч
IMAGE s40q;//boss��ֹ
IMAGE s41p;//boss˲��Ԥ��
IMAGE s41b;//boss˲������
IMAGE s41f;//boss˲������
IMAGE s41t;//boss˲����Ч
IMAGE s42lp;//boss��ΧԤ��
IMAGE s42lb;//boss��Χ����
IMAGE s42lf;//boss��Χ����
IMAGE s42lt;//boss��Χ��Ч
IMAGE s42rp;//boss�ҷ�ΧԤ��
IMAGE s42rb;//boss�ҷ�Χ����
IMAGE s42rf;//boss�ҷ�Χ����
IMAGE s42rt;//boss�ҷ�Χ��Ч
IMAGE s43q;//boss�ָ���Ч
IMAGE s44q;//bossȫ������
IMAGE s44t;//bossȫ����Ч
IMAGE img_strat;//��ʼ����
IMAGE img_bad;//�����
IMAGE img_happy;//�ý��
IMAGE cover;//����
IMAGE help;//����
IMAGE page0;//����
IMAGE page1;//����
IMAGE page2;//����
IMAGE page3;//����
IMAGE page4;//����
IMAGE page5;//����
IMAGE page6;//����
IMAGE page7;//����
IMAGE page8;//����
IMAGE page9;//����
IMAGE page10;//����

IMAGE life;//�ն���Ѫ����
IMAGE life_break;//���С��Ѫ�����ļ��ͼƬ
IMAGE sm_life[5];//С��Ѫ����
IMAGE sm2_life[5];
IMAGE sm3_life[5];
IMAGE sister_life;//С���Ѫ����

struct small_monster//����С��
{
	int sm_x;//xλ��
	int sm_y;//yλ��
	float life;//����ֵ
	float power;//������
	float v;//�ƶ��ٶ�
	int mons1fightflag;//�жϹ���1�Ƿ������
	int mons1;//����1��������֡����,�����Ҹ���
	int mons1runflag;//����1�н�ʱ������������ֹ���˶���
	int flag1;//�н�����0��1��
};
small_monster sm[5];//��һ�׶ι���
small_monster sm2[5];//�ڶ��׶ι���
small_monster sm3[5];//�����׶ι���
small_monster sm4;//boss
int flag_sm2 = 0;
int flag_sm3 = 0;
int flag_sm4 = 0;
//int man_x = 500;
//int man_y = 630;
int stock_x;//��ʯx
int stock_y;//��ʯy


//knightΪ����ͼ��knight_x��knight_yΪ����ͼ�����ڵ�λ�á������Ͻǵ�
int knight_x = 700, knight_y = 600;

//����Ѫ��
int knight_life = 2000;

//����ͼ��
IMAGE knight;

//isLimit�����ж�knight�Ƿ񵽴ﻭ���⣬�����Ϊ0�������Ϊ1
//knight_x���ֵΪ600����СֵΪ0��knight_y���ֵΪ1340����СֵΪ0
//isLimit��run���ʹ�ã���isLimitΪ1ʱ����run��ֵ��Ϊ-1
int isLimit = 0;

//iΪ����ʱ�����������ÿ����һ�����ܣ�i��Ϊ0��ÿ��ѭ���𽥼�1���ۼӵ�20���ܽ��������м��ܶ�ʹ��i���ܣ�����Ϊ�˱����ظ�ʹ�ü���
int i = 0;

//��ʾ�Ƿ���ǰ���ܣ�-1Ϊ��ֹ��1Ϊ���ܡ�֮����ʹ��-1��1������ʹ��1��0������Ϊ���ǿ���ͨ����run=-run�����л�״̬������ʹ��һ����
int run = -1;

//����vlΪ1�����ң�vlΪ-1������Ĭ��Ϊ1��
//ͬʱ��vlҲ�����ٶȣ���ͨ��knight_x+=vl��ʵ��knight���ƶ���Ϊ1�������ƶ���Ϊ-1�������ƶ�
int vl = 1;

//��Ծ���ܣ�jumpΪ1����Ծ��jumpΪ-1����ֹ��jump_Ϊ��Ծʱ������ͼ��֮������-1��1������ʹ��1��0������Ϊ���ǿ���ͨ����jump=-jump���л�״̬������ʹ��һ����
int jump = 0;
IMAGE jump_;

//vr����Ծ���ٶ�
int vr = 7;

//���ּ���
int flash = 0;
IMAGE flash_;

//����a��killa_Ϊ����a��ͼ�񣬿���ǰ������Ķ�
int killa = 0;
IMAGE killa_;

//����b��killb_Ϊ����b��ͼ�������ɫ����
int killb = 0;
IMAGE killb_;
#define b_kill 20

//����c������ǰ����������ɫ�⻷��killc_effort_Ϊ�⻷ͼ��
int killc = 0;
IMAGE killc_effort;
#define c_kill 5

//����d����ɫ���飬���ܲ����ظ�ʹ�ã�dl�Ǻ�ɫ����ķ���
int killd = 0;
int d_time = 0;
IMAGE killd_effort;
int dx = 0, dy = 0;
int dl = 1;
int isD = 0;
int d_effort_time = 0;
#define d_kill 15

//����e,�ü��ܻᷢ��һ����ɫ��ʯ��ex��ey�Ǳ�ʯ�����꣬���ܲ����ظ�ʹ�ã�el����ɫ��ʯ�ķ���
int kille = 0;
int e_time = 0;
IMAGE kille_effort;
IMAGE kille_effort_effort;
int ex = 0, ey = 0;
int el = 1;
int isE = 0;
int e_effort_time = 0;
#define e_kill 10

//�趨knight���������½���ÿ���½�gravity
int gravity = 10;

//����ש��λ������
int brick1_x = 230;
int brick1_y = 433;
int brick2_x = 568;
int brick2_y = 255;
int brick3_x = 908;
int brick3_y = 433;

//������������жϿն����Ƿ��ܵ�������0��δ�ܵ�������1���ܵ����������ܵ��������л�ͼƬ��δʹ��
int isAttack = 0;

//�ش̣��ش̻�ͻȻ�ӵ���ð��������˺�����С200*200
IMAGE spike;
int spike_effort_time = 0;
int iSpike = 0;
#define spike_kill 5

//����������������ͻȻ���֣�������������ס���޷��˶����޷�ʩչ�κμ��ܣ���С200*200
IMAGE dream;
int dream_time = 0;
int isDream = 0;

//���Ͷ��棬�����ͻȻ���֣����붾��Ӵ����ж�
IMAGE bug;
int isBug = 0;
int bug_time = 0;
int bug_x;
int bug_y;
#define bug_kill 10

//��Ѫʯ����Ѫʯ��ͻȻ���֣��Ӵ���Ѫʯ���Ѫ
IMAGE stone;
int iStone = 0;
int stone_x;
int stone_y;
int stone_time = 0;
#define REBLOOD 15

//���֣����ֻ�ͻȻ������߽�ð��������˺�����С200*120
IMAGE ghost_left;
IMAGE ghost_right;
int isGhost = 1;
int ghost_y;
int ghost_time = 0;
#define ghost_kill 5;

//���ؽ�����õ��Ķ���
IMAGE load_back;
IMAGE load_life;
IMAGE load_life_head;
int load_life_len = 0;
IMAGE load_hint;

//������������жϽ����ĸ�show������
int game = 1;

//�Զ��庯��������
void updateWithoutInput();
void updateWithInput();
void gameover();
//����һ�������ж����������Ƿ��ཻ�ĺ���
int isCover(int x1, int x2, int y1, int y2, int a1, int a2, int b1, int b2);
//�������ͼ����
void putimg(int picture_x, int picture_y, IMAGE* picture);
//showload�������� 
void showload();

//int flag1[5];//�н�����0��1��
//�浵
//��ʼ�˵�
//��Ϸ��ʼ��
//��ͼ��ײ
//��������
//�����ƶ�
small_monster* create_monster(small_monster sm[]);//����1�Ķ���

void small_monster_run(small_monster sm[]);//����1һ���ж�
void pre();//loading
void show();	 //��Ϸ��ʾģ��,����4
void showm1(int i);//����1����,����5
small_monster* create_monster2(small_monster sm2[]);//����2���壬����6
void small_monster_run2(int i);//����2һ���ж�������7
void showm2(int i);//����2չʾ������8
small_monster* create_monster3(small_monster sm3[]);//��������3,����9
void small_monster_run3(int i);	 //С��3���˶�,����10
void showm3(int i);//С��3չʾ������11
small_monster* create_monster4();//����boss��С��㣬����12
void small_monster_run4();//С����ƶ�������13
void showm4();//С���չʾ������14
void startMenu();//��ʼ����
void endline();//�����׶�
void help_me();//��������
void story_begin();//���չ����д��startmeau��
void happy_story();//happy end
void bad_story();//bad end
int main()
{
	initgraph(1400, 780);// ��ȡͼƬ����ͼ����
	create_monster(sm);
	create_monster2(sm2);
	create_monster3(sm3);
	create_monster4();

	pre();

	startMenu();
	showload();
	BeginBatchDraw();

	//char s[10] = "how";
	//ExMessage m;		// ������Ϣ����
	mciSendString(_T("stop load_music"), NULL, 0, NULL);
	mciSendString(_T("open music\\mons1.mp3 alias mons_music"), NULL, 0, NULL);
	mciSendString(_T("play mons_music repeat"), NULL, 0, NULL);     //ѭ����������
	while (knight_life > 0 && sm4.life > 0)
	{
		show();
		FlushBatchDraw();
		small_monster_run(sm);//С��1�ƶ�
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
small_monster* create_monster(small_monster sm[])//����С��,����1
{
	srand((unsigned int)time(NULL));
	//for (int i = 0; i < 5; i++)
	//	printf("%d ", sm[i].sm_y);
	for (int i = 0; i < 5; i++)
	{
		sm[i].sm_x = rand() % (1100 + 1) + 200;//�����200-1200
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
small_monster* create_monster2(small_monster sm2[])//��������2
{
	srand((unsigned int)time(NULL));
	//for (int i = 0; i < 5; i++)
	//	printf("%d ", sm[i].sm_y);
	for (int i = 0; i < 5; i++)
	{
		sm2[i].sm_x = rand() % (1100 + 1) + 200;//�����200-1200
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
small_monster* create_monster3(small_monster sm3[])//��������3
{
	srand((unsigned int)time(NULL));
	//for (int i = 0; i < 5; i++)
	//	printf("%d ", sm[i].sm_y);
	for (int i = 0; i < 5; i++)
	{
		sm3[i].sm_x = rand() % (1100 + 1) + 200;//�����200-1200
		sm3[i].sm_y = rand() % (630 + 1) + 0;//�����0-630
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
	sm4.sm_x = 1100;//boss��x
	sm4.sm_y = 570;//boss���ڵ���
	sm4.life = 6000;
	sm4.power = 50;
	sm4.v = 10;
	sm4.mons1 = 0;
	sm4.mons1fightflag = 0;
	sm4.mons1runflag = 0;
	sm4.flag1 = 0;
	return &sm4;
}
void pre()//�����ʼ��������3
{
	loadimage(&stone, _T("�ն�����ʿ\\stone.png"), 80, 100);
	loadimage(&ghost_left, _T("�ն�����ʿ\\ghost_left.png"), 200, 120);
	loadimage(&ghost_right, _T("�ն�����ʿ\\ghost_right.png"), 200, 120);
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

	loadimage(&spike, _T("�ն�����ʿ\\spike.png"), 300, 100);
	loadimage(&dream, _T("�ն�����ʿ\\dream1.png"), 200, 200);

	loadimage(&firstbk, _T("�ն�����ʿ\\�ն�����ʿ��ͼ.png"), 1400, 780);
	loadimage(&img_strat, _T("�ն�����ʿ\\��ʼ����.png"), 1400, 780);
	loadimage(&img_happy, _T("�ն�����ʿ\\happy_end.png"), 1400, 780);
	loadimage(&img_bad, _T("�ն�����ʿ\\bad_end.png"), 1400, 780);
	loadimage(&help, _T("�ն�����ʿ\\����.png"), 1400, 780);
	loadimage(&page0, _T("�ն�����ʿ\\����page0.png"), 1400, 780);
	loadimage(&page1, _T("�ն�����ʿ\\����page1.png"), 1400, 780);
	loadimage(&page2, _T("�ն�����ʿ\\����page2.png"), 1400, 780);
	loadimage(&page3, _T("�ն�����ʿ\\����page3.png"), 1400, 780);
	loadimage(&page4, _T("�ն�����ʿ\\����page4.png"), 1400, 780);
	loadimage(&page5, _T("�ն�����ʿ\\����page5.png"), 1400, 780);
	loadimage(&page6, _T("�ն�����ʿ\\����page6.png"), 1400, 780);
	loadimage(&page7, _T("�ն�����ʿ\\����page7.png"), 1400, 780);
	loadimage(&page8, _T("�ն�����ʿ\\����page8.png"), 1400, 780);
	loadimage(&page9, _T("�ն�����ʿ\\����page9.png"), 1400, 780);
	loadimage(&page10, _T("�ն�����ʿ\\����page10.png"), 1400, 780);
	loadimage(&s1rq, _T("�ն�����ʿ\\С��1�Ҿ�ֹ��ʽ͸��.png"), 100, 100);
	loadimage(&s1rr, _T("�ն�����ʿ\\С��1��������ʽ͸��.png"), 100, 100);
	loadimage(&s1rp, _T("�ն�����ʿ\\С��1��Ԥ����ʽ͸��.png"), 100, 100);
	loadimage(&s1rb, _T("�ն�����ʿ\\С��1��������ʽ͸��.png"), 100, 100);
	loadimage(&s1rf, _T("�ն�����ʿ\\С��1��������ʽ͸��.png"), 100, 100);
	loadimage(&s1rt, _T("�ն�����ʿ\\С��1����Ч��ʽ͸��.png"), 100, 100);
	loadimage(&s1lq, _T("�ն�����ʿ\\С��1��ֹ��ʽ͸��.png"), 100, 100);
	loadimage(&s1lr, _T("�ն�����ʿ\\С��1��������ʽ͸��.png"), 100, 100);
	loadimage(&s1lp, _T("�ն�����ʿ\\С��1��Ԥ����ʽ͸��.png"), 100, 100);
	loadimage(&s1lb, _T("�ն�����ʿ\\С��1��������ʽ͸��.png"), 100, 100);
	loadimage(&s1lf, _T("�ն�����ʿ\\С��1��������ʽ͸��.png"), 100, 100);
	loadimage(&s1lt, _T("�ն�����ʿ\\С��1����Ч��ʽ͸��.png"), 100, 100);
	loadimage(&s2lq, _T("�ն�����ʿ\\С��2��������ʽ͸��.png"), 75, 75);
	loadimage(&s2lb, _T("�ն�����ʿ\\С��2��������ʽ͸��.png"), 75, 75);
	loadimage(&s2lf, _T("�ն�����ʿ\\С��2��������ʽ͸��.png"), 75, 75);
	loadimage(&s2lt, _T("�ն�����ʿ\\С��2����Ч��ʽ͸��.png"), 75, 75);
	loadimage(&s2rq, _T("�ն�����ʿ\\С��2��������ʽ͸��.png"), 75, 75);
	loadimage(&s2rb, _T("�ն�����ʿ\\С��2��������ʽ͸��.png"), 75, 75);
	loadimage(&s2rf, _T("�ն�����ʿ\\С��2��������ʽ͸��.png"), 75, 75);
	loadimage(&s2rt, _T("�ն�����ʿ\\С��2����Ч��ʽ͸��.png"), 75, 75);
	loadimage(&s3lq, _T("�ն�����ʿ\\С��3���ж���ʽ͸��.png"), 60, 60);
	loadimage(&s3lb, _T("�ն�����ʿ\\С��3��������ʽ͸��.png"), 60, 60);
	loadimage(&s3lf, _T("�ն�����ʿ\\С��3��������ʽ͸��.png"), 60, 60);
	loadimage(&s3lt, _T("�ն�����ʿ\\С��3����Ч��ʽ͸��.png"), 60, 60);
	loadimage(&s3rq, _T("�ն�����ʿ\\С��3���ж���ʽ͸��.png"), 60, 60);
	loadimage(&s3rb, _T("�ն�����ʿ\\С��3��������ʽ͸��.png"), 60, 60);
	loadimage(&s3rf, _T("�ն�����ʿ\\С��3��������ʽ͸��.png"), 60, 60);
	loadimage(&s3rt, _T("�ն�����ʿ\\С��3����Ч��ʽ͸��.png"), 60, 60);
	loadimage(&s40q, _T("�ն�����ʿ\\boss��ֹ.png"), 100, 100);
	loadimage(&s41p, _T("�ն�����ʿ\\boss˲��Ԥ��.png"), 100, 100);
	loadimage(&s41b, _T("�ն�����ʿ\\boss˲������.png"), 100, 100);
	loadimage(&s41f, _T("�ն�����ʿ\\boss˲������.png"), 100, 100);
	loadimage(&s41t, _T("�ն�����ʿ\\boss˲����Ч.png"), 300, 160);
	loadimage(&s42lp, _T("�ն�����ʿ\\boss��ΧԤ��.png"), 100, 100);
	loadimage(&s42lb, _T("�ն�����ʿ\\boss��Χ����.png"), 100, 100);
	loadimage(&s42lf, _T("�ն�����ʿ\\boss��Χ����.png"), 100, 100);
	loadimage(&s42lt, _T("�ն�����ʿ\\boss��Χ��Ч.png"), 500, 100);
	loadimage(&s42rp, _T("�ն�����ʿ\\boss�ҷ�ΧԤ��.png"), 100, 100);
	loadimage(&s42rb, _T("�ն�����ʿ\\boss�ҷ�Χ����.png"), 100, 100);
	loadimage(&s42rf, _T("�ն�����ʿ\\boss�ҷ�Χ����.png"), 100, 100);
	loadimage(&s42rt, _T("�ն�����ʿ\\boss�ҷ�Χ��Ч.png"), 500, 100);
	loadimage(&s43q, _T("�ն�����ʿ\\boss�ָ�.png"), 100, 100);
	loadimage(&s44q, _T("�ն�����ʿ\\bossȫ������.png"), 100, 100);
	loadimage(&s44t, _T("�ն�����ʿ\\bossȫ����Ч.png"), 225, 225);
}
void show()	 //��Ϸ��ʾģ��,����4
{
	putimg(0, 0, &firstbk);//չʾ��ͼ
	putimage(0, 0, &life);//չʾ��ʿѪ����

	srand((unsigned int)time(NULL));

	//�ش������
	if ((iSpike == 1) && (knight_y == 600)) {
		putimg(knight_x - 120, knight_y + 20, &spike);
	}
	//�����������
	if (isDream == 1) {
		putimg(knight_x - 70, knight_y - 70, &dream);
	}
	//���������
	if (isBug == 1) {
		/*bug_x = rand() % 1200;
		bug_y = rand() % 250;*/
		putimg(bug_x, bug_y, &bug);
		/*bug_x = knight_x;
		bug_y = knight_y;
		putimg(knight_x, knight_y, &bug);*/
	}
	//���������
	if ((isGhost == 1) && ((knight_x < 60) || (knight_x > 1280))) {
		putimg(0, knight_y - 50, &ghost_left);
		putimg(1200, knight_y - 50, &ghost_right);
	}
	//��Ѫʯ�����
	if (iStone == 1) {
		putimg(stone_x, stone_y, &stone);
	}
	//���
	for (int i = 0; i < 5; i++)//����Ķ���չʾ
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
			small_monster_run3(i);//С��3�ƶ�
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
				mciSendString(_T("play boss_music repeat"), NULL, 0, NULL);     //ѭ����������
				for (int j = 0; j < 5; j++)
					sm4.life = 6000;
			}
			if (sm4.flag1 == 0)
			{
				sm4.flag1 = rand() % (100 + 1) + 1;//����С�����ԣ�flag1Ϊ����ѡȡ
				small_monster_run4();
			}
			showm4();
			////��������������¼��С����Ѫ��
			//loadimage(&sister_life, _T("right\\green.png"), (sm4.life / 6000.0) * 1400, 10);
			////�����������������С����Ѫ��
			//putimage(0, 10, &sister_life);
			//putimage(0, 10, &life_break);


		}
	}

	//���Ǽ��������
	if (vl == 1) {
		//��Ծ�����
		if (jump == 1) {
			putimg(knight_x, knight_y, &knight);
			knight_y -= vr;
		}
		else {
			putimg(knight_x, knight_y, &knight);
		}
		//killa�����
		if (killa == 1) {
			putimg(knight_x, knight_y, &knight);
			knight_x += 5;
		}
		//killb�����
		if (killb == 1) {
			putimg(knight_x + 60, knight_y, &killb_);
		}
		//killc�����
		if (killc == 1) {
			putimg(knight_x - 30, knight_y - 30, &killc_effort);
		}
		//killd�����
		if (killd == 1) {
			putimg(knight_x, knight_y, &knight);
		}
		//kille�����
		if (kille == 1) {
			putimg(knight_x, knight_y, &knight);
			putimg(knight_x + 60, knight_y, &kille_effort_effort);
		}
	}
	else {
		//��Ծ�����
		if (jump == 1) {
			putimg(knight_x, knight_y, &knight);
			knight_y -= vr;
		}
		else {
			putimg(knight_x, knight_y, &knight);
		}
		//killa�����
		if (killa == 1) {
			putimg(knight_x, knight_y, &knight);
			knight_x -= 5;
		}
		//killb�����
		if (killb == 1) {
			putimg(knight_x - 60, knight_y, &killb_);
		}
		//killc�����
		if (killc == 1) {
			putimg(knight_x - 30, knight_y - 30, &killc_effort);
		}
		//killd�����
		if (killd == 1) {
			putimg(knight_x, knight_y, &knight);
		}
		//kille�����
		if (kille == 1) {
			putimg(knight_x, knight_y, &knight);
			putimg(knight_x - 60, knight_y, &kille_effort_effort);
		}

	}
	//killd�ӵ������
	if (isD == 1) {
		putimg(dx, dy, &killd_effort);
	}
	//kille�ӵ������
	if (isE == 1) {
		putimg(ex, ey, &kille_effort);
	}
}
void small_monster_run(small_monster sm[])	 //С��1���˶�������2
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
				sm[i].sm_x += 1;//flagΪ0��
			}
			else
			{
				sm[i].sm_x -= 1;//Ϊ1��
			}
		}
	}

}
void showm1(int i)
{
	game = 1;

	//С��Ѫ������
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
		sm[i].mons1fightflag = 1;//�ҹ����жϿ�ʼ����
	else if (knight_x < sm[i].sm_x && knight_x >= sm[i].sm_x - 200 && sm[i].mons1fightflag == 0
		&& knight_y > sm[i].sm_y && knight_y <= sm[i].sm_y + 100)
		sm[i].mons1fightflag = -1;//�󹥻��жϿ�ʼ����


	//�ҹ���
	if (sm[i].mons1fightflag > 0)//yes
	{
		if (sm[i].mons1 < 10)//Ԥ��
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rp);
			sm[i].mons1++;
		}
		else if (sm[i].mons1 < 20)//����
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rb);
			sm[i].mons1++;
		}
		else//����
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rf);
			putimg(sm[i].sm_x + 50, sm[i].sm_y, &s1rt);
			sm[i].mons1++;//25֡��Ѫ
			if (sm[i].mons1 == 25 && knight_x > sm[i].sm_x && knight_x <= sm[i].sm_x + 200
				&& knight_y >= sm[i].sm_y && knight_y < sm[i].sm_y + 100) {
				knight_life -= 30;//���ǵ�Ѫ
				loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			}

			if (sm[i].mons1 == 30)
			{
				sm[i].mons1fightflag = 0;
				sm[i].mons1 = 0;
			}
		}
	}

	//�󹥻�
	if (sm[i].mons1fightflag < 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;
		if (sm[i].mons1 > -10)//Ԥ��
		{
			//putimg(sm[i].sm_x, sm[i].sm_y, &cover);
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lp);
			sm[i].mons1--;
		}
		else if (sm[i].mons1 > -20)//����
		{
			//putimg(sm[i].sm_x, sm[i].sm_y, &cover);
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lb);
			sm[i].mons1--;
		}
		else// if (a.mons1 > -30)//����
		{
			//putimg(sm[i].sm_x, sm[i].sm_y, &cover);
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lf);
			//putimg(sm[i].sm_x, sm[i].sm_y, &cover);
			putimg(sm[i].sm_x - 50, sm[i].sm_y, &s1lt);
			sm[i].mons1--;
			if (sm[i].mons1 == -25 && knight_x < sm[i].sm_x && knight_x >= sm[i].sm_x - 200
				&& knight_y > sm[i].sm_y && knight_y <= sm[i].sm_y + 100) {
				knight_life -= 30;//���ǵ�Ѫ
				loadimage(&life, _T("right\\life.png"), (knight_life / 2000.0) * 1400, 10);
			}
			if (sm[i].mons1 == -30)
			{
				sm[i].mons1fightflag = 0;
				sm[i].mons1 = 0;
			}
		}
	}

	//�ƶ�
	if (sm[i].mons1fightflag == 0)
	{
		if (sm[i].flag1 == 0 && sm[i].mons1runflag >= 0)//�Ҿ�ֹ
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rq);
			sm[i].mons1runflag++;
			if (sm[i].mons1runflag == 10)
				sm[i].mons1runflag = -1;
		}
		else if (sm[i].flag1 == 0 && sm[i].mons1runflag < 0)//������
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1rr);
			sm[i].mons1runflag--;
			if (sm[i].mons1runflag == -10)
				sm[i].mons1runflag = 1;
		}
		else if (sm[i].flag1 == 1 && sm[i].mons1runflag >= 0)//��ֹ
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lq);
			sm[i].mons1runflag++;
			if (sm[i].mons1runflag == 10)
				sm[i].mons1runflag = -1;
		}
		else//������
		{
			putimg(sm[i].sm_x, sm[i].sm_y, &s1lr);
			sm[i].mons1runflag--;
			if (sm[i].mons1runflag == -10)
				sm[i].mons1runflag = 1;
		}
	}
	//sm[i].life -= 10;
}
void small_monster_run2(int i)	 //С��2���˶�������2
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
			sm2[i].sm_x += 2;//flagΪ0��
		}
		else
		{
			sm2[i].sm_x -= 2;//Ϊ1��
		}
	}

}
void showm2(int i)//����2�����
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
		sm2[i].mons1fightflag = 1;//�ҹ����жϿ�ʼ����
	else if (knight_x < sm2[i].sm_x && knight_x >= sm2[i].sm_x - 100 && sm2[i].mons1fightflag == 0
		&& knight_y > sm2[i].sm_y - 100 && knight_y <= sm2[i].sm_y + 100)
		sm2[i].mons1fightflag = -1;
	//if(sm2[i].sm_y==605&&sm2[i].mons1fightflag==0)
	//	sm2[i].mons1fightflag = 1;
	//�ҹ���
	//if(������Ϊ0)//�ж������Ƿ��ڹ�����Χ��
	//mons1fightflag = 1;
	if (sm2[i].mons1fightflag > 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;

		if (sm2[i].mons1 < 10)//����
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2rb);
			sm2[i].mons1++;
		}
		else// if (a.mons1 < 30)//����
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

	//�󹥻�
	//if(������Ϊ0)//�ж������Ƿ��ڹ�����Χ��
	//mons1fightflag = 1;
	if (sm2[i].mons1fightflag < 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;
		if (sm2[i].mons1 > -10)//����
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2lb);
			sm2[i].mons1--;
		}
		else// if (a.mons1 > -30)//����
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


	//�ƶ�
	if (sm2[i].mons1fightflag == 0)
	{
		if (sm2[i].flag1 == 0)//�Ҿ�ֹ
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2rq);
		}
		else if (sm2[i].flag1 == 1)//��ֹ
		{
			//putimg(sm2[i].sm_x, sm2[i].sm_y, &cover);
			putimg(sm2[i].sm_x, sm2[i].sm_y, &s2lq);
		}
	}
	//sm2[i].life -= 10;
}
void small_monster_run3(int i)	 //С��3���˶�
{
	//srand((unsigned int)time(NULL));
	//	sm3[i].flag1 = rand() % (1 + 1) + 0;
	if (sm3[i].life > 0)
	{
		if (sm3[i].flag1 == 0 && knight_x > sm3[i].sm_x)//x����,����
		{
			sm3[i].sm_x += 2;//flagΪ0��
		}
		else if (sm3[i].flag1 == 0 && knight_x < sm3[i].sm_x)//x����������
		{
			sm3[i].sm_x -= 2;//Ϊ0x��
		}
		else if (sm3[i].flag1 == 1 && knight_y > sm3[i].sm_y)//y����������
		{
			sm3[i].sm_y += 2;//Ϊ1y��
		}
		else if (sm3[i].flag1 == 1 && knight_y < sm3[i].sm_y)
		{
			sm3[i].sm_y -= 2;//Ϊ1y��
		}
	}

}
void showm3(int i)//����2�����
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
		sm3[i].mons1fightflag = 1;//�ҹ����жϿ�ʼ����
	else if (knight_x < sm3[i].sm_x && knight_x >= sm3[i].sm_x - 100 && sm3[i].mons1fightflag == 0
		&& knight_y > sm3[i].sm_y - 100 && knight_y <= sm3[i].sm_y + 100)
		sm3[i].mons1fightflag = -1;
	//if(sm3[i].sm_y==630&&sm3[i].mons1fightflag==0)
	//	sm3[i].mons1fightflag = 1;
	//�ҹ���
	//if(������Ϊ0)//�ж������Ƿ��ڹ�����Χ��
	//mons1fightflag = 1;
	if (sm3[i].mons1fightflag > 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;

		if (sm3[i].mons1 < 10)//����
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3rb);
			sm3[i].mons1++;
		}
		else// if (a.mons1 < 30)//����
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

	//�󹥻�
	//if(������Ϊ0)//�ж������Ƿ��ڹ�����Χ��
	//mons1fightflag = 1;
	if (sm3[i].mons1fightflag < 0)//yes
	{
		//if (a.sm_y != 630)
		//	mons1fightflag = 0;
		if (sm3[i].mons1 > -10)//����
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3lb);
			sm3[i].mons1--;
		}
		else// if (a.mons1 > -30)//����
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


	//�ƶ�
	if (sm3[i].mons1fightflag == 0)
	{
		if (knight_x >= sm3[i].sm_x)//�Ҿ�ֹ
		{
			//putimg(sm3[i].sm_x, sm3[i].sm_y, &cover);
			putimg(sm3[i].sm_x, sm3[i].sm_y, &s3rq);
		}
		else//��ֹ
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
		if (sm4.flag1 < 50)//��ͨ��Χ����
		{
			;
		}
		else if (sm4.flag1 < 80)//˲�ƹ���
		{
			//sm4.sm_x = knight_x;
			//sm4.sm_y = knight_y - 50;
		}
		else if (sm4.flag1 < 90)//����
		{
			sm4.sm_x = 1100;
			sm4.sm_y = 200;
		}
		else//ȫ��
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
		if (sm4.flag1 < 40)//��ͨ��Χ����
		{
			if (sm4.mons1 == 0 && knight_x <= sm4.sm_x)
				sm4.mons1fightflag = 1;//�󹥻�
			else if (sm4.mons1 == 0 && knight_x > sm4.sm_x)
				sm4.mons1fightflag = -1;//�ҹ���
			if (sm4.mons1fightflag > 0)//����
			{
				if (sm4.mons1 < 120)//��Ԥ��
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42lp);
					sm4.mons1++;
				}
				else if (sm4.mons1 < 160)//������
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42lb);
					sm4.mons1++;
				}
				else if (sm4.mons1 < 200)//������
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
			if (sm4.mons1fightflag < 0)//�ҳ���
			{
				if (sm4.mons1 > -120)//��Ԥ��
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42rp);
					sm4.mons1--;
				}
				else if (sm4.mons1 > -160)//������
				{
					//putimg(sm4.sm_x, sm4.sm_y, &cover);
					putimg(sm4.sm_x, sm4.sm_y, &s42rb);
					sm4.mons1--;
				}
				else if (sm4.mons1 > -200)//������
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
		else if (sm4.flag1 < 80)//˲�ƹ���
		{
			if (sm4.mons1 == 0)//˲��
			{
				//sm4.sm_x = knight_x;
				//sm4.sm_y = knight_y + 50;
				sm4.mons1++;
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s41p);
			}
			else if (sm4.mons1 < 120)//Ԥ��
			{
				//putimg(sm4.sm_x, sm4.sm_y, &cover);
				putimg(sm4.sm_x, sm4.sm_y, &s41p);
				sm4.mons1++;
				if (sm4.sm_y >= 5)
					sm4.sm_y -= 3;
			}
			else if (sm4.mons1 < 160)//����
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
			else if (sm4.mons1 < 200)//����
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
		else if (sm4.flag1 < 90)//����
		{
			//putimg(sm4.sm_x, sm4.sm_y, &cover);
			putimg(sm4.sm_x, sm4.sm_y, &s40q);
			//putimg(sm4.sm_x, sm4.sm_y - 50, &cover);
			putimg(sm4.sm_x, sm4.sm_y - 50, &s43q);
			sm4.mons1++;
			sm4.life++;//��600Ѫ
			if (sm4.mons1 == 600)
			{
				sm4.flag1 = 0;
				sm4.mons1fightflag = 0;
				sm4.mons1 = 0;
				sm4.sm_x = rand() % (1200 + 1) + 100;
				sm4.sm_y = rand() % (380 + 1) + 200;
			}
		}
		else if (sm4.flag1 >= 90)//ȫ��
		{
			if (sm4.mons1 == 0)
			{
				sm4.mons1++;
				stock_x = rand() % (700 + 1) + 400;
				stock_y = 0;
			}
			else if (sm4.mons1 < 100)//Ԥ��
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

	//�����������루jumpʱ���������䣩��
	if (jump == 1) {
		knight_y += 0;
	}
	else {
		knight_y += gravity;
	}

	//�߽��жϣ�
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

	//��һ��ש�߽��жϣ�
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
	//�ڶ���ש�߽��жϣ�
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
	//������ש�߽��жϣ�
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

	//killd����ʱ���жϣ�
	if (d_effort_time == 20) {
		isD = 0;
	}
	else {
		d_effort_time++;
	}
	//kille����ʱ���жϣ�
	if (e_effort_time == 20) {
		isE = 0;
	}
	else {
		e_effort_time++;
	}

	//knight����ʱ���������룺
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

		//��Ծ���룺
		if (jump == 1) {
			loadimage(&knight, _T("right\\jump.png"), 60, 60);
		}
		else {
			loadimage(&knight, _T("right\\knight1.png"), 60, 60);
		}

		//���ܣ�killa�����룺
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

		//killb���룺
		if (killb == 1) {
			//killb��С�ֵĴ������Ѫ��20*20==400��ע�⣺��Ȼ�·������Ѫ��Ϊ20������ʵ����Ҫ����20����Ϊi��0������19����׶��ڣ�����ִ�м�Ѫ���
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

		//killc���룺
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

		//killd�������룺
		if (killd == 1) {
			loadimage(&knight, _T("right\\kill_d.png"), 60, 60);
		}
		//killd�ӵ����룺
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

		//kille�������룺
		if (kille == 1) {
			loadimage(&knight, _T("right\\kille.png"), 60, 60);
			loadimage(&kille_effort_effort, _T("right\\kille_effort_effort.png"), 60, 60);
		}
		//kille�ӵ����룺
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

	//knight����ʱ����������
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
		//��Ծ���룺
		if (jump == 1) {
			loadimage(&knight, _T("left\\jump.png"), 60, 60);
		}
		else {
			loadimage(&knight, _T("left\\knight1.png"), 60, 60);
		}
		//���ܣ�killa�����룺
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
		//killb���룺
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

		//killc���룺
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
		//killd�������룺
		if (killd == 1) {
			loadimage(&knight, _T("left\\kill_d.png"), 60, 60);
		}
		//killd�ӵ����룺
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

		//kille���ﶯ�����룺
		if (kille == 1) {
			loadimage(&knight, _T("left\\kille.png"), 60, 60);
			loadimage(&kille_effort_effort, _T("left\\kille_effort_effort.png"), 60, 60);
		}
		//kille�ӵ����룺
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



	//���������룺
	if (isDream == 1) {
		if (dream_time % 2) {
			loadimage(&dream, _T("�ն�����ʿ\\dream2.png"), 200, 200);
		}
		else {
			loadimage(&dream, _T("�ն�����ʿ\\dream1.png"), 200, 200);
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


	//�ش����룺
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

	//�������룺
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
			loadimage(&bug, _T("�ն�����ʿ\\bug1.png"), 150, 400);
		}
		else if (bug_time < 4) {
			loadimage(&bug, _T("�ն�����ʿ\\bug2.png"), 150, 400);
		}
		else if (bug_time < 6) {
			loadimage(&bug, _T("�ն�����ʿ\\bug3.png"), 150, 400);
		}
		else if (bug_time < 8) {
			loadimage(&bug, _T("�ն�����ʿ\\bug4.png"), 150, 400);
		}
		else if (bug_time < 10) {
			loadimage(&bug, _T("�ն�����ʿ\\bug5.png"), 150, 400);
		}
		else if (bug_time < 12) {
			loadimage(&bug, _T("�ն�����ʿ\\bug6.png"), 150, 400);
		}
		else if (bug_time < 14) {
			loadimage(&bug, _T("�ն�����ʿ\\bug1.png"), 150, 400);
		}
		else if (bug_time < 16) {
			loadimage(&bug, _T("�ն�����ʿ\\bug2.png"), 150, 400);
		}
		else if (bug_time < 18) {
			loadimage(&bug, _T("�ն�����ʿ\\bug3.png"), 150, 400);
		}
		else if (bug_time < 20) {
			loadimage(&bug, _T("�ն�����ʿ\\bug4.png"), 150, 400);
		}
		else if (bug_time < 22) {
			loadimage(&bug, _T("�ն�����ʿ\\bug5.png"), 150, 400);
		}
		else if (bug_time < 24) {
			loadimage(&bug, _T("�ն�����ʿ\\bug6.png"), 150, 400);
		}
		else if (bug_time < 26) {
			loadimage(&bug, _T("�ն�����ʿ\\bug1.png"), 150, 400);
		}
		else if (bug_time < 28) {
			loadimage(&bug, _T("�ն�����ʿ\\bug2.png"), 150, 400);
		}
		else if (bug_time < 30) {
			loadimage(&bug, _T("�ն�����ʿ\\bug3.png"), 150, 400);
		}
		else if (bug_time < 32) {
			loadimage(&bug, _T("�ն�����ʿ\\bug4.png"), 150, 400);
		}
		else if (bug_time < 34) {
			loadimage(&bug, _T("�ն�����ʿ\\bug5.png"), 150, 400);
		}
		else if (bug_time < 36) {
			loadimage(&bug, _T("�ն�����ʿ\\bug6.png"), 150, 400);
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

	//�������룺
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

	//��Ѫʯ���룺
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


	//����ն���Ѫ������2000��
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
void putimg(int  picture_x, int picture_y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�
	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}

}
void startMenu() // ��ʼ�˵�����
{
	ExMessage m;
	putimage(0, 0, &img_strat);//��ʾ����
	//rectangle(1100, 105, 1305, 180);
	//rectangle(1100, 225, 1305, 300);
	//rectangle(1100, 350, 1305, 425);
	mciSendString(_T("open music\\begin1.mp3 alias begin_music"), NULL, 0, NULL);
	//openָ�����Ҫ���ŵ����֣�alias�����ƶ���ǰ���ļ�·���ı������Ժ���Ҫ��������ļ�ֱ��ʹ����������Ϳ�����.
	//��������ļ������ǵ�debug�ļ�����ͬһĿ¼�£��Ϳ���������������д·����ֱ����������
	//��������ļ��������������͵�д���·����
	//��: D���µ�demoĿ¼��һ����1.MP3���ļ�
	//mciSendString("open demo\\1.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString(_T("play begin_music repeat"), NULL, 0, NULL);     //ѭ����������
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
	putimage(0, 0, &help);//��ʾ����;
	//rectangle(1130, 650, 1335, 725);
	//rectangle(1130, 505, 1335, 580);
	ExMessage m;
	while (1)
	{
		m = getmessage(EM_MOUSE);//_getch();// Press any key to continue
		if (m.message == WM_LBUTTONDOWN && (m.x > 1130 && m.x < 1335 && m.y>505 && m.y < 580)) {
			putimage(0, 0, &page0);//����
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
	mciSendString(_T("play happy_music repeat"), NULL, 0, NULL);     //ѭ����������
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
	mciSendString(_T("play bad_music repeat"), NULL, 0, NULL);     //ѭ����������
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
		mciSendString(_T("play load_music repeat"), NULL, 0, NULL);     //ѭ����������
		loadimage(&load_life, _T("load\\load_life.png"), load_life_len, 15);
		outtextxy(640, 650, L"*****LOADING*****");
		outtextxy(570, 675, L"*Although there is nothing to load.......*");
		putimage(400, 700, &load_life);
		putimage(load_life_len + 400, 700, &load_life_head);

		switch (show) {
		case 1:putimg(550, 300, &hint1);
			outtextxy(550, 400, L"*--------------------------���ĵش�--------------------------*");
			break;
		case 2:putimg(550, 100, &load_hint);
			outtextxy(550, 400, L"*---����㱻��������ס����ᶯ������---*");
			break;
		case 3:putimg(625, 100, &load_hint);
			outtextxy(550, 400, L"*-----------------���Ķ��棬����ʱ����-----------------*");
			break;
		case 4:putimg(600, 200, &load_hint);
			outtextxy(550, 400, L"*-----------��Ҫ�����߽磬�й��ֳ�û-----------*");
			break;
		case 5:putimg(660, 250, &load_hint);
			outtextxy(550, 400, L"*----------����Ӳӵ�ʯͷ�������Ѫ----------*");
			break;
		}
		FlushBatchDraw();
		if (load_life_len < 120) {
			loadimage(&hint1, _T("�ն�����ʿ\\spike.png"), 300, 100);
			show = 1;
			Sleep(10);
		}
		else if (load_life_len < 240) {
			loadimage(&load_hint, _T("�ն�����ʿ\\dream1.png"), 300, 300);
			show = 2;
			Sleep(10);
		}
		else if (load_life_len < 360) {
			loadimage(&load_hint, _T("�ն�����ʿ\\bug1.png"), 150, 400);
			show = 3;
			Sleep(10);
		}
		else if (load_life_len < 480) {
			loadimage(&load_hint, _T("�ն�����ʿ\\ghost_right.png"), 200, 120);
			show = 4;
			Sleep(10);
		}
		else {
			loadimage(&load_hint, _T("�ն�����ʿ\\stone.png"), 80, 100);
			show = 5;
			Sleep(10);
		}
		load_life_len += 1;
	}
	EndBatchDraw();

}