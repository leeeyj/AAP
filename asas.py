#문자열 쓰기
#hello.text 파일을 쓰기모드(w)로 열기 {w는 쓰다 write의 w}
#파일 객체=open(파일이름,파일모드)   파일객체.write('문자열')   파일객체.close()  {파일열기-> 파일쓰기-> 파일닫기}
file = open('hel;o.text','w')
file.write('Hello, world!')
file.close()

#문자열 읽기 
#hello.text 파일을 읽기모드(r)로 열기 {r는 읽다 read의 r} 
file = open('hello.text','r')
s=file.read() #파일에서 문자열 읽기
print(s)  #Hello world! 출력 
file.close() 
