import requests
import urllib.request
from bs4 import BeautifulSoup
import time
import random
session = requests.session()
import os

header = {
        "Accept-Encoding": "gzip, deflate",
        "Accept-Language": "zh-CN,zh;q=0.8",
        "Connection": "keep-alive",
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.157 Safari/537.36",
        "Content-Type": "application/x-www-form-urlencoded",
        "Host": "www.kekenet.com"
}
# 请设置运行间隔,单位:秒
timeval = 2

class english_conversation:
    listen_name = ''
    listen_url = ''
    listen_content = ''

def get_listen():
    file = open('listen_conversation.txt','r')
    all_url = file.readlines()
    count = 0
    for url in all_url:
        page = session.get(str(url).strip(),headers=header)
        if page.status_code != 200:
            print('%s is broken %s'%(url,page.status_code))
            print(page.text)
            return
        listen_object = english_conversation()
        soup =BeautifulSoup(page.text.encode(encoding='ISO-8859-1'),'html.parser')
        # 找到标题
        title = soup.find('h1',{'id':'nrtitle'})
        if title == None:
            print('%s get title is broken'%url)
            continue
        listen_object.listen_name = title.get_text()
        # 找到对话内容
        context_en = soup.find_all('div',{'class':'qh_en'})
        context_cn = soup.find_all('div',{'class':'qh_zg'})
        context = []
        if context_en == None or context_cn == None:
            print('%s get context is broken'%url)
            continue
        text_en = [text.get_text()+'\n' for text in context_en if text.get_text()]
        text_cn = [text.get_text()+'\n' for text in context_cn if text.get_text()]
        for x in range(0,len(context_cn)):
            context.append(text_en[x])
            context.append(text_cn[x])
        listen_object.listen_content = context

        # 检查获取
        #print(listen_object.listen_name)
        #print(listen_object.listen_content)

        #开始下载
        pre_download_url= "http://www.kekenet.com/mp3/%s.shtml"%url[url.find('menu')+5:url.find('.shtml')]
        pre_download_html = session.get(pre_download_url,headers=header)
        pre_download_soup = BeautifulSoup(pre_download_html.text.encode(encoding='ISO-8859-1'),'html.parser')
        download_list = [mp3.get('href') for mp3 in pre_download_soup.find_all('a',{'target':'_blank'}) if mp3.has_attr('href') and mp3.get('href').find('Sound')>0]
        random_num = random.randint(0,len(download_list)-1)
        print('download from (the random num is %s)%s '%(random_num,download_list[random_num]))
        try:
            # 名字处理
            listen_object.listen_name = ''.join(listen_object.listen_name.split(' '))
            listen_object.listen_name = listen_object.listen_name[listen_object.listen_name.find('第'):].replace(':','-')
            print(listen_object.listen_name)
            if os.path.exists('./%s'%(listen_object.listen_name)) == False:
                os.mkdir('./%s'%(listen_object.listen_name))
            urllib.request.urlretrieve(download_list[random_num], "%s/%s.mp3"%(listen_object.listen_name,listen_object.listen_name))
            open("%s/%s.txt"%(listen_object.listen_name,listen_object.listen_name),'w+').writelines(listen_object.listen_content)
        except:
            print('download is timeout')
        print('%s th . Download is done,wait %s s' % (count + 1, timeval))
        print('你已经下载%s个听力了,Ctrl+C可停止运行' % str(count + 1))
        time.sleep(timeval)
        count += 1

if __name__ == '__main__':
    get_listen()