#include <Windows.h>
#include "glew.h"
#include "glut.h"
#define _USE_MATH_DEFINES //���w���C�u������M_PI��L���ɂ���
#include <math.h> //���w���C�u�����̃C���N���[�h

#define W_H		1280 //Window��
#define W_V		720 //Window����

#include "CMain.h"

CMain Main;

/* display�֐�
1�b�Ԃ�60����s�����
*/
void display() {
	//�e�o�b�t�@�[���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//�s��̃��[�h�����f���r���[�ɂ���
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�̍s���P�ʍs��ɂ���
	glLoadIdentity();

	Main.MainLoop();

	//��ʂɕ\��
	glutSwapBuffers();
}

//�֐��̃v���g�^�C�v�錾
void reshape(int, int);
void idle();

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);	//�f�B�X�v���C���[�h�ݒ�
	//�E�B���h�E�̐ݒ�
	glutInitWindowSize(W_H, W_V);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("�}�b�v�G�f�B�^�[ | 0.0FPS | 00:00.000");	//�E�B���h�E�쐬
	system("TITLE conhost.exe");
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);	//�N���A�F���O���[�ɐݒ�

	glewInit();

//	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

//���C�g�̐ݒ�
	//�Œ�V�F�[�_�[�p
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//���b�V���V�F�[�_�[�p
//	CLight::getLight(0)->setDir(CVector3D(0, -1, 1).GetNormalize());
//	CLight::getLight(0)->setColor(CVector3D(0.9f, 0.9f, 0.9f), CVector3D(1.0f, 1.0f, 1.0f));

	//�e��֐��ݒ�
	glutDisplayFunc(display);	//�`�掞�̊֐����w��
	glutReshapeFunc(reshape);	//�E�B���h�E�ό`���̊֐����w��
	glutIdleFunc(idle);			//�ҋ@���̊֐����w��

	//���C�����[�v
	glutMainLoop();

	return;
}

/*�E�B���h�E�T�C�Y�ύX���̏���
void reshape(int width, int height)
width:��ʕ�
height:��ʍ���
*/
void reshape(int width, int height) {
	glViewport(0, 0, width, height);	//��ʂ̕`��G���A�̎w��
//3D Setting
	//CCamera::getCamera()->SetSize(width, height);
	//glMatrixMode(GL_PROJECTION);		//�s����v���W�F�N�V�������[�h�֕ύX
	//glLoadIdentity();
	//gluPerspective(75.0, (double)width / (double)height, 1.0, 1000.0);
	//gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//2D Setting
	glMatrixMode(GL_PROJECTION);		//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();				//�s���������
	gluOrtho2D(-W_H / 2, W_H / 2, -W_V / 2, W_V / 2);	//��ʂ̍��W�n��ݒ�
	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glLoadIdentity();				//�s���������

}

LARGE_INTEGER last_time;	//�O��̃J�E���^�l
//�P�b�ԂɂU�O��`�悷��悤�ɒ��߂���
void idle() {
	LARGE_INTEGER freq;		//��b������̃J�E���^��
	LARGE_INTEGER time;		//����̃J�E���^�l

	//��b�Ԃ̃J�E���^�����擾
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//���݂̃V�X�e���̃J�E���g�����擾
		QueryPerformanceCounter(&time);

		//���̃J�E���g-�O��̃J�E���g < 1�b������̃J�E���g����60�Ŋ���(1/60�b������̃J�E���g��)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//�`�悷��֐����Ă�
	display();
}
