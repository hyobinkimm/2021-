import distutils
from distutils.core import setup
from typing import NewType
from botocore.utils import S3ControlEndpointSetter
from dataclasses import dataclass
from sys import exit
import time
import os
import random
import botocore
import boto3
import shutil
import pygame

width=390
height=540
isNew=False
scores=[]
name=""
high_score=0
students=[]
cnt=0 # 학생수
running=True

# 키보드로 이름 입력받기
shiftDown=False
validChars = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./"
shiftChars = '~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:"ZXCVBNM<>?'

class TextBox(pygame.sprite.Sprite):
  def __init__(self):
    pygame.sprite.Sprite.__init__(self)
    self.text = ""
    cur=os.getcwd()
    font_=cur+"/dist/LexiGulim.ttf"
    self.font = pygame.font.Font(font_, 25)
    self.image = self.font.render("Enter name(English)", False, [255, 0, 0])
    self.rect = self.image.get_rect()
  def add_chr(self, char):
    global shiftDown
    if char in validChars and not shiftDown:
        self.text += char
    elif char in validChars and shiftDown:
        self.text += shiftChars[validChars.index(char)]
    self.update()
  def update(self):
    old_rect_pos = self.rect.center
    self.image = self.font.render(self.text, False, [0, 0, 0])
    self.rect = self.image.get_rect()
    self.rect.center = old_rect_pos

class TextBox_(pygame.sprite.Sprite):
  def __init__(self):
    pygame.sprite.Sprite.__init__(self)
    self.text = ""
    cur=os.getcwd()
    font_=cur+"/dist/LexiGulim.ttf"
    self.font = pygame.font.Font(font_, 25)
    self.image = self.font.render("Continue? Y/N", False, [255, 0, 0])
    self.rect = self.image.get_rect()
  def add_chr(self, char):
    global shiftDown
    if char in validChars and not shiftDown:
        self.text += char
    elif char in validChars and shiftDown:
        self.text += shiftChars[validChars.index(char)]
    self.update()
  def update(self):
    old_rect_pos = self.rect.center
    self.image = self.font.render(self.text, False, [0, 0, 0])
    self.rect = self.image.get_rect()
    self.rect.center = old_rect_pos
###

def rank():
    global students
    students_=[]
    download_dll()
    read_dll()
    students_=sorted(students, key=lambda student: student[1]) # 일단 stduents들 정렬
    students_.reverse()
    f=open("score.txt", "w")
    
    for i in range(len(students_)):
        x=str(i+1)
        s=x+"등 | 이름 : "+students_[i][0]+" | 점수 :  "+str(students_[i][1])+"\n"
        f.writelines(s)

    f.close()
    
def caution_download():
    BASE_DIR = os.getcwd()
    IMAGE_DIR = os.path.join(BASE_DIR, 'images')
    AWS_ACCESS_KEY_ID = "[AKIARY7HHQEDOGECBCM6]"
    AWS_SECRET_ACCESS_KEY = "[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]"
    AWS_DEFAULT_REGION = "ap-northeast-2"
    AWS_BUCKET_NAME = "gamecaution"

    client = boto3.client('s3',
                        aws_access_key_id=AWS_ACCESS_KEY_ID,
                        aws_secret_access_key=AWS_SECRET_ACCESS_KEY,
                        region_name=AWS_DEFAULT_REGION
                        )
    s3 = boto3.resource('s3')

    buckets = s3.Bucket(name=AWS_BUCKET_NAME)



    # S3 Client 생성
    s3 = boto3.client('s3')

    # S3에 있는 현재 버킷리스트의 정보를 가져온다
    response = s3.list_buckets()

    #print(response)

    # response에 담겨있는 Buckets의 이름만 가져와 buckets 변수에 배열로 저장
    buckets = [bucket['Name'] for bucket in response['Buckets']]

    # S3 버킷 리스트를 출력
    #print("Bucket List: %s" % buckets)


    # 업로드할 파일 이름
    filename = "주의사항(필독).txt"

    # 업로드할 버킷
    bucket_name = 'gamecaution'

    # 첫 번째 매개변수 : 로컬에서 올릴 파일이름
    # 두 번째 매개변수 : S3 버킷 이름
    # 세 번째 매개변수 : 버킷에 저장될 파일 이름.
    #s3.upload_file(filename, bucket_name, filename)
    s3.download_file(bucket_name,filename,'주의사항(필독).txt')

def download_dll():
    BASE_DIR = os.getcwd() # 현재 작업 디렉토리 반환
    IMAGE_DIR = os.path.join(BASE_DIR, 'images')
    AWS_ACCESS_KEY_ID = "[AKIARY7HHQEDOGECBCM6]"
    AWS_SECRET_ACCESS_KEY = "[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]"
    AWS_DEFAULT_REGION = "ap-northeast-2"
    AWS_BUCKET_NAME = "kmyobinshoot"

    client = boto3.client('s3',
        aws_access_key_id=AWS_ACCESS_KEY_ID,
        aws_secret_access_key=AWS_SECRET_ACCESS_KEY,
        region_name=AWS_DEFAULT_REGION
        )
    s3 = boto3.resource('s3')

    buckets = s3.Bucket(name=AWS_BUCKET_NAME)

    # S3 Client 생성
    s3 = boto3.client('s3')

    # S3에 있는 현재 버킷리스트의 정보를 가져온다
    response = s3.list_buckets()

    # response에 담겨있는 Buckets의 이름만 가져와 buckets 변수에 배열로 저장
    buckets = [bucket['Name'] for bucket in response['Buckets']]

    # 업로드할 파일 이름
    filename = "score.dll"

    # 업로드할 버킷
    bucket_name = 'kmyobinshoot'

    #s3.upload_file(filename, bucket_name, filename)
    s3.download_file(bucket_name,filename,'score.dll')

def upload():
    BASE_DIR = os.getcwd()
    IMAGE_DIR = os.path.join(BASE_DIR, 'images')
    AWS_ACCESS_KEY_ID = "[AKIARY7HHQEDOGECBCM6]"
    AWS_SECRET_ACCESS_KEY = "[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]"
    AWS_DEFAULT_REGION = "ap-northeast-2"
    AWS_BUCKET_NAME = "kmyobinshoot"

    client = boto3.client('s3',
        aws_access_key_id=AWS_ACCESS_KEY_ID,
        aws_secret_access_key=AWS_SECRET_ACCESS_KEY,
        region_name=AWS_DEFAULT_REGION
        )
    s3 = boto3.resource('s3')

    buckets = s3.Bucket(name=AWS_BUCKET_NAME)

    # S3 Client 생성
    s3 = boto3.client('s3')

    # S3에 있는 현재 버킷리스트의 정보를 가져온다
    response = s3.list_buckets()

    # response에 담겨있는 Buckets의 이름만 가져와 buckets 변수에 배열로 저장
    buckets = [bucket['Name'] for bucket in response['Buckets']]

    # 업로드할 파일 이름
    filename = "score.dll"

    # 업로드할 버킷
    bucket_name = 'kmyobinshoot'

    s3.upload_file(filename, bucket_name, filename)

def installer():
    link = os.getlogin() # user name 가져오기

    nowdr="./.aws"
    fordr="C:/Users/"+link+"/.aws" # server 판단
    
    distutils.dir_util.copy_tree(nowdr, fordr)

def read_dll():
    global students
    students=[] # 초기화
    f=open("score.dll", 'r')
    cnt=0

    while True:
        line=f.readline() # 한 줄씩 읽어서 line에 저장
        if not line: break
        data=line.split() # 띄어쓰기 기준으로 나눠서 data에 저장
        students.append([data[0], int(data[1])])
        cnt+=1 # 학생수
    f.close()

def login():
    global name, high_score, cnt, students

    #별명 입력받기#
    textBox=TextBox() # class 선언
    shiftDown=False

    textBox.rect.center=[210,240]
    running=True

    while(running):
        screen.fill([255,255,255])
        screen.blit(textBox.image, textBox.rect)
        pygame.display.flip()
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                #haha=False
                running = False
                exit()
            if e.type == pygame.KEYUP:
                if e.key in [pygame.K_RSHIFT, pygame.K_LSHIFT]:
                    shiftDown = False
            if e.type == pygame.KEYDOWN:
                textBox.add_chr(pygame.key.name(e.key))
                if e.key == pygame.K_SPACE:
                    textBox.text += " "
                    textBox.update()
                if e.key in [pygame.K_RSHIFT, pygame.K_LSHIFT]:
                    shiftDown = True
                if e.key == pygame.K_BACKSPACE:
                    textBox.text = textBox.text[:-1]
                textBox.update()
                if e.key == pygame.K_RETURN:
                    if len(textBox.text) > 0:
                        name=textBox.text # name에 저장
                        running = False

    
    download_dll() # score.dll 다운로드
    read_dll() # score.dll 읽어서 student에 저장

    for i in range(len(students)):
        if(students[i][0]==name): # 이미 등록되어있는 사람
            high_score=int(students[i][1]) # high_score에 점수 받아옴
            return

    high_score=0
    

def regist():
    global isNew, name, high_score, cnt

    cnt+=1 # 학생수 한 명 증가

    x=open("score.dll", 'a')
    isNew=True
    students.append([name, 0]) # 신규 사용자는 당연히 점수가 0점
    high_score=0

    y=name+" "+'0'+"\n"
    x.writelines(y)
    x.close()
    upload() # score.dll 수정해서 업로드

def initialize():
    global back, screen, ship, rock, explosion, clock, missile, coin
    global rock_size, rock_width, rock_height, rock_x, rock_y
    global ship_size, ship_width, ship_height, ship_x, ship_y
    global coin_size, coin_width, coin_height, coin_x, coin_y
    global missile_sound, explosion_sound, gameover_sound, coin_sound
    global name, score

    pygame.init() # 무적권 해줘야됨
    pygame.display.set_caption("INCOM SHOOTING GAME") # 인컴..
    
    cur=os.getcwd()
    back_=cur+"/dist/back.jpg"
    ship_=cur+"/dist/spaceship.png"
    rock_=cur+"/dist/rock.png"
    explosion_=cur+"/dist/explosion.png"
    explosion_s=cur+"/dist/bang.wav"
    missile_=cur+"/dist/missile.png"
    missile_s=cur+"/dist/missile.wav"
    coin_=cur+"/dist/coin.png"
    coin_s=cur+"/dist/coin.wav"
    gameover_s=cur+"/dist/gameover.mp3"
    

    screen=pygame.display.set_mode((width,height)) # 제일 기초가 되는 screen 화면 비율
    back=pygame.image.load(back_) # back은 우주 사진

    '''# 우주선 #'''
    ship=pygame.image.load(ship_) # ship은 우주선 사진
    ship_size=ship.get_rect().size # 이미지 크기와 같은 사각형 객체 만들기
    ship_width=ship_size[0] # 가로
    ship_height=ship_size[1] # 세로

    '''# 운석 #'''
    rock=pygame.image.load(rock_) # rock은 운석 사진
    rock_size=rock.get_rect().size # 이미지 크기와 같은 사각형 객체 만들기
    rock_width=rock_size[0] # 가로
    rock_height=rock_size[1] # 세로
    
    '''# 폭발 #'''
    explosion=pygame.image.load(explosion_) # explosion은 폭발 사진
    explosion_sound=pygame.mixer.Sound(explosion_s) # 미사일로 운석을 맞추면 나오는 소리
    missile=pygame.image.load(missile_) # missile은 미사일 사진
    missile_sound=pygame.mixer.Sound(missile_s) # 미사일이 발사될 때 나오는 소리

    '''# 보너스 코인 #'''
    coin=pygame.image.load(coin_)
    coin_size=coin.get_rect().size
    coin_width=coin_size[0]
    coin_height=coin_size[1]
    coin_sound=pygame.mixer.Sound(coin_s)

    gameover_sound=pygame.mixer.Sound(gameover_s) # 운석 충돌 & 지나친 운석 많은 경우
    clock=pygame.time.Clock()

def show_back(x, y):
    global screen, back
    screen.blit(back, (x,y))

def show_ship(x, y):
    global back, ship    
    screen.blit(ship, (x,y))  

def show_rock(x, y):
    global screen, rock
    screen.blit(rock, (x,y))

def show_missile(x, y):
    global screen, missile
    screen.blit(missile, (x,y))

def show_explosion(x, y):
    global screen, explosion
    screen.blit(explosion, (x,y))

def show_coin(x, y):
    global screen, coin
    screen.blit(coin, (x,y))

def show_score(count):
    global screen
    cur=os.getcwd()
    font_=cur+"/dist/LexiGulim.ttf"
    font=pygame.font.Font(font_, 20)
    text=font.render("점수: "+str(count), True, (255,255,255))
    screen.blit(text, (10,0))

def show_hp(count):
    global screen
    cur=os.getcwd()
    font_=cur+"/dist/LexiGulim.ttf"
    font=pygame.font.Font(font_, 20)
    text=font.render('놓친 운석 : ' + str(3-count), True, (255,0,0))
    screen.blit(text, (270,0))

def gameover():
    global screen
    gameover_sound.play() # 사운드 출력
    cur=os.getcwd()
    font_=cur+"/dist/malgunbd.ttf"
    font=pygame.font.Font(font_, 60)
    text=font.render("GAMEOVER", True,(255,0,0))
    text_size=text.get_rect()
    screen.blit(back, (0,0))
    screen.blit(text, text_size)
    pygame.display.update()

    time.sleep(2)
    pygame.quit()
    

    initialize()
    run()
    
def save_score(a):
    global high_score
    global isNew
    isNew=True

    if(a>=high_score): # 방금 끝남 게임 점수가 high_score보다 높을 경우
        high_score=a # high_score을 a로 바꾼다
    
    download_dll()
    read_dll()

    ''' 이미 등록되어 있는 사람인 경우 '''
    for i in range(len(students)):
        if(students[i][0]==name): # 찾아서
            students[i][1]=high_score # high_score로 저장
            isNew=False
    
    ''' 신규 가입한 사람인 경우 '''
    if(isNew==True):
        students.append([name, high_score])
    
    f=open("score.dll", 'w') # 덮어쓰기
    for i in range(len(students)):
        y=str(students[i][0])+" "+str(students[i][1])+"\n"
        f.writelines(y)
    f.close() # score.dll 덮어 썼으니 닫고

    upload() # 이를 aws에 올린다

def run():
    global back, screen, ship, rock, explosion, clock, coin
    global ship_x, ship_y, rock_x, rock_y, coin_x, coin_y
    global score, high_score
    rock_passed=0

    # x : 가로, y : 세로
    
    # 우주선 초기 설정
    ship_x=width*0.45 # 위치
    ship_y=height*0.9
    to_x_left=0 # 위치 변화
    to_x_right=0
    to_y_up=0
    to_y_down=0

    # 방해물 초기 설정
    rock_x=random.randrange(0, width-rock_width) # x좌표를 0 부터 (가로 너비 - 돌 너비)
    rock_y=0 # y좌표는 0에서 내려오는 것으로 고정
    rock_speed=2 # 초기 speed는 2
    
    # 코인 초기 설정
    coin_x=random.randrange(0, width-coin_width)
    coin_y=0
    coin_speed=5

    # 점수 관련
    score=0 # 총 점수
    get=30 # 맞춘 운석 당 포인트

    #방해물 맞으면 true
    shot=False 
    
    # 미사일 좌표(2차원 배열)
    missile_xy=[] # x좌표 , y좌표

    show_back(0,0) # 바탕화면 깔기
    show_ship(ship_x,ship_y) # 초기 우주선 위치 조정 후 깔기
    done=False 

    while not done:
        for event in pygame.event.get():
            if(event.type==pygame.QUIT): # 닫기 누르면
                done=True # done이 true가 되고 while문을 빠져나옴
                pygame.quit()
                exit()
            if(event.type==pygame.KEYDOWN): # 키가 눌러져 있으면 KEYDOWN
                # 한 번 누를 때마다 3씩 변함
                if(event.key==pygame.K_LEFT):
                    to_x_left-=3
                elif(event.key==pygame.K_RIGHT):
                    to_x_right+=3
                elif(event.key==pygame.K_UP):
                    to_y_up-=3
                elif(event.key==pygame.K_DOWN):
                    to_y_down+=3
                elif(event.key==pygame.K_SPACE): # 미사일 발사
                    missile_sound.play() # 소리 재생
                    missile_x=ship_x+ship_width/2 # 미사일의 x좌표 : 우주선 x좌표 + (우주선 너비/2)
                    # 우주선의 중앙이 미사일의 초기 x좌표
                    missile_y=ship_y-ship_height # 미사일의 y좌표 : 우주선 y좌표 - 우주선 높이
                    missile_xy.append([missile_x, missile_y]) # 미사일 좌표 배열에 append
            
            if(event.type==pygame.KEYUP): # 키를 떼면 KEYUP
                if(event.key==pygame.K_LEFT):
                    to_x_left=0
                elif(event.key==pygame.K_RIGHT):
                    to_x_right=0
                elif(event.key==pygame.K_UP):
                    to_y_up=0
                elif(event.key==pygame.K_DOWN):
                    to_y_down=0

        show_back(0,0)

        ship_x+=to_x_left+to_x_right # 우주선 좌표를 to_x, to_y만큼 바꿈
        ship_y+=to_y_up+to_y_down

        # 화면 밖을 빠져나갔을 경우 조정
        if(ship_x<0):  # 0보다 작으면
            ship_x=0
        elif(ship_x>width-ship_width): 
            ship_x=width-ship_width
        if(ship_y<0):
            ship_y=0
        elif(ship_y>height-ship_height):
            ship_y=height-ship_height


        # 충돌 체크
        if(ship_y<=rock_y and rock_y<=ship_y+ship_height) or \
            (rock_y+rock_height>=ship_y and rock_y+rock_height<=ship_y+ship_height):
            if(rock_x>=ship_x and rock_x<=ship_x+ship_width) or \
                (rock_x+rock_width>=ship_x and rock_x+rock_width<=ship_x+ship_width):
                save_score(score) # 점수 저장
                rank()
                gameover() 

        # 우주선이 코인에 닿았을 때
        if(ship_y<=coin_y and coin_y<=ship_y+ship_height) or \
            (coin_y+coin_height>=ship_y and coin_y+coin_height<=ship_y+ship_height):
            if(coin_x>=ship_x and coin_x<=ship_x+ship_width) or \
                (coin_x+coin_width>=ship_x and coin_x+coin_width<=ship_x+ship_width):
                coin_sound.play()
                score+=100 # 코인은 100점
                coin_x=random.randrange(0, width-coin_width)
                coin_y=0
                coin_speed+=0.15
                if(coin_speed>=10):
                    coin_speed=10

        show_ship(ship_x,ship_y)

        if(len(missile_xy)!=0):
            for m_x, m_y in missile_xy:
                show_missile(m_x, m_y)
       
        if(len(missile_xy)!=0): 
            m_xy=[]
            for i, m_xy in enumerate(missile_xy): # 미사일 요소에 대해 반복
                m_xy[1]-=3 # 미사일 y좌표 -3(위로 이동)
                missile_xy[i][1]=m_xy[1]

                # 미사일이 방해물을 쐈을 경우
                if(m_xy[1]<=rock_y):
                    if((m_xy[0]>=rock_x and m_xy[0]<=rock_x+rock_width)or\
                        (m_xy[0]+20>=rock_x and m_xy[0]<=rock_x)): # 일단 미사일 좌표가 방해물 좌표보다 작아야함
                        missile_xy.remove(m_xy)
                        explosion_sound.play()
                        shot=True
                        score+=50
                if(m_xy[1]<=0): # 미사일이 화면 밖을 벗어나면
                    try:
                        missile_xy.remove(m_xy) # 미사일 제거
                    except:
                        pass

        

        show_score(score)
        show_hp(rock_passed)
        rock_y+=rock_speed # 운석이 아래로 떨어지는 중
        coin_y+=coin_speed # 코인이 아래로 떨어지는 중
         
        
        if(rock_y>=height): # 운석이 그냥 떨어질 경우
            rock_x=random.randrange(0, width-rock_width)
            rock_y=0
            rock_passed+=1 # rock_passed가 +1
            if(rock_passed==3):
                save_score(score)
                rank()
                gameover()
        
        if(coin_y>=height): # 코인이 그냥 떨어질 경우
            coin_x=random.randrange(0, width-coin_width)
            coin_y=0

        if(shot==True):
            score+=get # 운석 맞히면 30점 , 35점, 40점 얻음
            get+=5
            show_explosion(rock_x, rock_y)
            rock_x=random.randrange(0, width-rock_width)
            rock_y=0
            shot=False
            rock_speed+=0.15
            if(rock_speed>=8):
                rock_speed=8

        show_rock(rock_x, rock_y)
        show_coin(coin_x, coin_y)

        pygame.display.flip()
        pygame.event.pump()
        clock.tick(60)

        pygame.display.update()

    show_score(score)
    pygame.quit()
    exit()

caution_download()
installer() # server 확인
initialize() # 초기 설정
login()
run()