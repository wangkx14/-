#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include <functional>
#include <string>
using namespace std;
typedef struct User_basicinfo
{
	char id[15];//账号
	char paw[21];//密码
	char name[15];//姓名
	char sex[5];//性别
}Users;
void Login();//登录
void Regist();//注册
//密码的隐藏
void secretword(char key[]) {
	unsigned char c;
	int i = 0;
	while ((c = _getch()) != '\r') {
		if (i < 20 && isprint(c)) {
			key[i] = c;
			i++;
			putchar('*');
		}
		else if (i > 0 && c == '\b') {
			i--;
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
	}
	printf("\n");
	key[i] = '\0';
}
//crc循环冗余校验哈希加密
#define acl_uint64	unsigned long long int;

#define INITIALCRC    0xffffffffffffffffll

//acl_uint64 acl_hash_crc64(const void* buf, size_t len);
static unsigned long long int crc64_table[256] = {
		0x0ll,
		0x7ad870c830358979ll, 0xf5b0e190606b12f2ll, 0x8f689158505e9b8bll,
		0xc038e5739841b68fll, 0xbae095bba8743ff6ll, 0x358804e3f82aa47dll,
		0x4f50742bc81f2d04ll, 0xab28ecb46814fe75ll, 0xd1f09c7c5821770cll,
		0x5e980d24087fec87ll, 0x24407dec384a65fell, 0x6b1009c7f05548fall,
		0x11c8790fc060c183ll, 0x9ea0e857903e5a08ll, 0xe478989fa00bd371ll,
		0x7d08ff3b88be6f81ll, 0x7d08ff3b88be6f8ll, 0x88b81eabe8d57d73ll,
		0xf2606e63d8e0f40all, 0xbd301a4810ffd90ell, 0xc7e86a8020ca5077ll,
		0x4880fbd87094cbfcll, 0x32588b1040a14285ll, 0xd620138fe0aa91f4ll,
		0xacf86347d09f188dll, 0x2390f21f80c18306ll, 0x594882d7b0f40a7fll,
		0x1618f6fc78eb277bll, 0x6cc0863448deae02ll, 0xe3a8176c18803589ll,
		0x997067a428b5bcf0ll, 0xfa11fe77117cdf02ll, 0x80c98ebf2149567bll,
		0xfa11fe77117cdf0ll, 0x75796f2f41224489ll, 0x3a291b04893d698dll,
		0x40f16bccb908e0f4ll, 0xcf99fa94e9567b7fll, 0xb5418a5cd963f206ll,
		0x513912c379682177ll, 0x2be1620b495da80ell, 0xa489f35319033385ll,
		0xde51839b2936bafcll, 0x9101f7b0e12997f8ll, 0xebd98778d11c1e81ll,
		0x64b116208142850all, 0x1e6966e8b1770c73ll, 0x8719014c99c2b083ll,
		0xfdc17184a9f739fall, 0x72a9e0dcf9a9a271ll, 0x8719014c99c2b08ll,
		0x4721e43f0183060cll, 0x3df994f731b68f75ll, 0xb29105af61e814fell,
		0xc849756751dd9d87ll, 0x2c31edf8f1d64ef6ll, 0x56e99d30c1e3c78fll,
		0xd9810c6891bd5c04ll, 0xa3597ca0a188d57dll, 0xec09088b6997f879ll,
		0x96d1784359a27100ll, 0x19b9e91b09fcea8bll, 0x636199d339c963f2ll,
		0xdf7adabd7a6e2d6fll, 0xa5a2aa754a5ba416ll, 0x2aca3b2d1a053f9dll,
		0x50124be52a30b6e4ll, 0x1f423fcee22f9be0ll, 0x659a4f06d21a1299ll,
		0xeaf2de5e82448912ll, 0x902aae96b271006bll, 0x74523609127ad31all,
		0xe8a46c1224f5a63ll, 0x81e2d7997211c1e8ll, 0xfb3aa75142244891ll,
		0xb46ad37a8a3b6595ll, 0xceb2a3b2ba0eececll, 0x41da32eaea507767ll,
		0x3b024222da65fe1ell, 0xa2722586f2d042eell, 0xd8aa554ec2e5cb97ll,
		0x57c2c41692bb501cll, 0x2d1ab4dea28ed965ll, 0x624ac0f56a91f461ll,
		0x1892b03d5aa47d18ll, 0x97fa21650afae693ll, 0xed2251ad3acf6feall,
		0x95ac9329ac4bc9bll, 0x7382b9faaaf135e2ll, 0xfcea28a2faafae69ll,
		0x8632586aca9a2710ll, 0xc9622c4102850a14ll, 0xb3ba5c8932b0836dll,
		0x3cd2cdd162ee18e6ll, 0x460abd1952db919fll, 0x256b24ca6b12f26dll,
		0x5fb354025b277b14ll, 0xd0dbc55a0b79e09fll, 0xaa03b5923b4c69e6ll,
		0xe553c1b9f35344e2ll, 0x9f8bb171c366cd9bll, 0x10e3202993385610ll,
		0x6a3b50e1a30ddf69ll, 0x8e43c87e03060c18ll, 0xf49bb8b633338561ll,
		0x7bf329ee636d1eeall, 0x12b592653589793ll, 0x4e7b2d0d9b47ba97ll,
		0x34a35dc5ab7233eell, 0xbbcbcc9dfb2ca865ll, 0xc113bc55cb19211cll,
		0x5863dbf1e3ac9decll, 0x22bbab39d3991495ll, 0xadd33a6183c78f1ell,
		0xd70b4aa9b3f20667ll, 0x985b3e827bed2b63ll, 0xe2834e4a4bd8a21all,
		0x6debdf121b863991ll, 0x1733afda2bb3b0e8ll, 0xf34b37458bb86399ll,
		0x8993478dbb8deae0ll, 0x6fbd6d5ebd3716bll, 0x7c23a61ddbe6f812ll,
		0x3373d23613f9d516ll, 0x49aba2fe23cc5c6fll, 0xc6c333a67392c7e4ll,
		0xbc1b436e43a74e9dll, 0x95ac9329ac4bc9b5ll, 0xef74e3e19c7e40ccll,
		0x601c72b9cc20db47ll, 0x1ac40271fc15523ell, 0x5594765a340a7f3all,
		0x2f4c0692043ff643ll, 0xa02497ca54616dc8ll, 0xdafce7026454e4b1ll,
		0x3e847f9dc45f37c0ll, 0x445c0f55f46abeb9ll, 0xcb349e0da4342532ll,
		0xb1eceec59401ac4bll, 0xfebc9aee5c1e814fll, 0x8464ea266c2b0836ll,
		0xb0c7b7e3c7593bdll, 0x71d40bb60c401ac4ll, 0xe8a46c1224f5a634ll,
		0x927c1cda14c02f4dll, 0x1d148d82449eb4c6ll, 0x67ccfd4a74ab3dbfll,
		0x289c8961bcb410bbll, 0x5244f9a98c8199c2ll, 0xdd2c68f1dcdf0249ll,
		0xa7f41839ecea8b30ll, 0x438c80a64ce15841ll, 0x3954f06e7cd4d138ll,
		0xb63c61362c8a4ab3ll, 0xcce411fe1cbfc3call, 0x83b465d5d4a0eecell,
		0xf96c151de49567b7ll, 0x76048445b4cbfc3cll, 0xcdcf48d84fe7545ll,
		0x6fbd6d5ebd3716b7ll, 0x15651d968d029fcell, 0x9a0d8ccedd5c0445ll,
		0xe0d5fc06ed698d3cll, 0xaf85882d2576a038ll, 0xd55df8e515432941ll,
		0x5a3569bd451db2call, 0x20ed197575283bb3ll, 0xc49581ead523e8c2ll,
		0xbe4df122e51661bbll, 0x3125607ab548fa30ll, 0x4bfd10b2857d7349ll,
		0x4ad64994d625e4dll, 0x7e7514517d57d734ll, 0xf11d85092d094cbfll,
		0x8bc5f5c11d3cc5c6ll, 0x12b5926535897936ll, 0x686de2ad05bcf04fll,
		0xe70573f555e26bc4ll, 0x9ddd033d65d7e2bdll, 0xd28d7716adc8cfb9ll,
		0xa85507de9dfd46c0ll, 0x273d9686cda3dd4bll, 0x5de5e64efd965432ll,
		0xb99d7ed15d9d8743ll, 0xc3450e196da80e3all, 0x4c2d9f413df695b1ll,
		0x36f5ef890dc31cc8ll, 0x79a59ba2c5dc31ccll, 0x37deb6af5e9b8b5ll,
		0x8c157a32a5b7233ell, 0xf6cd0afa9582aa47ll, 0x4ad64994d625e4dall,
		0x300e395ce6106da3ll, 0xbf66a804b64ef628ll, 0xc5bed8cc867b7f51ll,
		0x8aeeace74e645255ll, 0xf036dc2f7e51db2cll, 0x7f5e4d772e0f40a7ll,
		0x5863dbf1e3ac9dell, 0xe1fea520be311aafll, 0x9b26d5e88e0493d6ll,
		0x144e44b0de5a085dll, 0x6e963478ee6f8124ll, 0x21c640532670ac20ll,
		0x5b1e309b16452559ll, 0xd476a1c3461bbed2ll, 0xaeaed10b762e37abll,
		0x37deb6af5e9b8b5bll, 0x4d06c6676eae0222ll, 0xc26e573f3ef099a9ll,
		0xb8b627f70ec510d0ll, 0xf7e653dcc6da3dd4ll, 0x8d3e2314f6efb4adll,
		0x256b24ca6b12f26ll, 0x788ec2849684a65fll, 0x9cf65a1b368f752ell,
		0xe62e2ad306bafc57ll, 0x6946bb8b56e467dcll, 0x139ecb4366d1eea5ll,
		0x5ccebf68aecec3a1ll, 0x2616cfa09efb4ad8ll, 0xa97e5ef8cea5d153ll,
		0xd3a62e30fe90582all, 0xb0c7b7e3c7593bd8ll, 0xca1fc72bf76cb2a1ll,
		0x45775673a732292all, 0x3faf26bb9707a053ll, 0x70ff52905f188d57ll,
		0xa2722586f2d042ell, 0x854fb3003f739fa5ll, 0xff97c3c80f4616dcll,
		0x1bef5b57af4dc5adll, 0x61372b9f9f784cd4ll, 0xee5fbac7cf26d75fll,
		0x9487ca0fff135e26ll, 0xdbd7be24370c7322ll, 0xa10fceec0739fa5bll,
		0x2e675fb4576761d0ll, 0x54bf2f7c6752e8a9ll, 0xcdcf48d84fe75459ll,
		0xb71738107fd2dd20ll, 0x387fa9482f8c46abll, 0x42a7d9801fb9cfd2ll,
		0xdf7adabd7a6e2d6ll, 0x772fdd63e7936bafll, 0xf8474c3bb7cdf024ll,
		0x829f3cf387f8795dll, 0x66e7a46c27f3aa2cll, 0x1c3fd4a417c62355ll,
		0x935745fc4798b8dell, 0xe98f353477ad31a7ll, 0xa6df411fbfb21ca3ll,
		0xdc0731d78f8795dall, 0x536fa08fdfd90e51ll, 0x29b7d047efec8728ll
};

//利用指针存放密码地址，压缩映射转化为固定长度输出
unsigned long long int acl_hash_crc64(const void* buf, size_t len)
{
	const unsigned char* ptr = (const unsigned char*)buf;
	unsigned long long int crc = INITIALCRC;

	while (len-- > 0) {
		crc = crc64_table[(int)((crc ^ *ptr++) & 0xff)] ^ (crc >> 8);
	}

	return crc;
}
int main()
{

	int input = -1;
	do
	{
		printf("\t\t\t------------------------------------\n");
		printf("\t\t\t|          1.用户登录              |\n");
		printf("\t\t\t|          2.用户注册              |\n");
		printf("\t\t\t|            0.退出                |\n");
		printf("\t\t\t------------------------------------\n");
		printf("请选择功能->");
		scanf("%d", &input);
		switch (input)
		{
		case 1:Login(); break;
		case 2:Regist(); break;
		case 0:puts("退出成功"); return 0;
		}
	} while (input);

	return 0;
}
void Regist()
{
	Users a = { 0 }, b = { 0 };
	char tmp[20] = { -1 };
	FILE* pf = NULL;
	pf = fopen("users.txt", "r");
	if (pf == NULL)
	{
		printf("注册时打开文件失败\n");
		return;
	}
	printf("\t\t\t欢迎来到注册界面\n\n");
	printf("\t\t\t输入账号->");
	scanf("%s", a.id);
	printf("输入成功!\n");

	fread(&b, sizeof(Users), 1, pf);
	//【判断】有没有注册过-比较字符串是否相等 
	//不相等->是否到文件尾 
	while (1)
	{
		if (strcmp(a.id, b.id) != 0)
		{
			if (feof(pf) == 0)
				fread(&b, sizeof(Users), 1, pf);
			else
			{
				printf("账号未注册过，将跳转到注册界面\n");
				system("pause");
				break;
			}
		}
		else
		{
			printf("该账号已注册过\n");
			fclose(pf); pf = NULL;
			return;
		}
	}
	//注册界面 
	printf("\t\t\t请输入姓名->");
	scanf("%s", a.name);
	printf("\t\t\t请输入性别:男/女->");
	do {
		getchar();
		scanf("%s", a.sex);
		if (strcmp(a.sex, "男") != 0 && strcmp(a.sex, "女") != 0)
			printf("\t\t\t输入错误，请重新输入->");
		else break;
	} while (1);

	printf("\t\t\t请输入密码->");
	secretword(a.paw);

	printf("\t\t\t请再输入一次密码->");
	do {
		secretword(tmp);
		if (strcmp(tmp, a.paw) != 0)
			printf("\t\t\t两次输入密码不一致，请再输入一次密码->");
		else break;
	} while (1);

	/*std::hash<const char*> hs;
	size_t mi = hs(a.paw);*/
	unsigned long long int mi = acl_hash_crc64(a.paw, strlen(a.paw));
	string str = std::to_string(mi);//int转字符串
	int nSize = str.size();//计算字符串长度
	memset(a.paw, 0, sizeof(a.paw));
	for (size_t i=0; i<nSize;i++)
	{
		a.paw[i] = str[i];
	}

	fclose(pf);	pf = NULL;
	pf = fopen("users.txt", "a");
	fwrite(&a, sizeof(Users), 1, pf);
	printf("\t\t\t注册成功!\n");
	fclose(pf);	pf = NULL;
	return;
}

void Login()
{
	Users a = { 0 }, b = { 0 };
	FILE* pf = fopen("users.txt", "r");
	if (pf == NULL)
	{
		printf("文件打开失败\n");
		return;
	}
	printf("欢迎来到登录界面!\n");
	printf("请输入账号->");
	scanf("%s", a.id);
	fread(&b, sizeof(Users), 1, pf);
	while (1)
	{
		if (strcmp(a.id, b.id) != 0)
		{
			if (feof(pf) == 0)
			{
				fread(&b, sizeof(Users), 1, pf);
			}
			else
			{
				printf("该账号不存在,请先注册\n");
				fclose(pf); pf = NULL;
				return;
			}
		}
		else
		{
			break;
		}

	}
	//输入密码
	printf("请输入密码->");
	do {
		secretword(a.paw);

		//std::hash<const char*> hs;
		//size_t mi = hs(a.paw);
		unsigned long long int mi = acl_hash_crc64(a.paw, strlen(a.paw));
		string str = std::to_string(mi);

		if (strcmp(str.c_str(), b.paw) != 0)
			printf("密码错误，请重新输入->");
		else break;
	} while (1);
	printf("登录成功!\n");
	fclose(pf); pf = NULL;
}
