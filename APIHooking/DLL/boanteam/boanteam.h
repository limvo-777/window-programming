// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// BOANTEAM_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef BOANTEAM_EXPORTS
#define BOANTEAM_API __declspec(dllexport)
#else
#define BOANTEAM_API __declspec(dllimport)
#endif

// �� Ŭ������ boanteam.dll���� ������ ���Դϴ�.
class BOANTEAM_API Cboanteam {
public:
	Cboanteam(void);
	// TODO: ���⿡ �޼��带 �߰��մϴ�.
};

extern BOANTEAM_API int nboanteam;

extern "C" BOANTEAM_API int fnboanteam(void);
