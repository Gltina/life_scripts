'''
    '����������С˵����'
    ֮ǰд������ÿ�ζ�������д,���ú���,��ϣ����һ��Сģ������������迴���Լ�ϲ������С˵.
    �����Ǿ���ϲ���ͻ���Ǯ������İ�(ϣ����˵��(ing)����)
    ʱ��:2017-03-07 08:35:44
    ����:ptsph@foxmail.com
'''

import requests
from bs4 import BeautifulSoup
import  time

'''
    http��ͷ,����hostһ����Ҫ�޸�
'''
header = {
        "Accept-Encoding": "gzip, deflate",
        "Accept-Language": "zh-CN,zh;q=0.8",
        "Connection": "keep-alive",
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.157 Safari/537.36",
        "Content-Type": "application/x-www-form-urlencoded",
        "Host": "www.hujuge.com"
}

session = requests.session()

def get_download_list(top_url,home_url,how_encoding,tag_name):
    page = session.get(str(home_url).strip(),headers=header)

    soup =BeautifulSoup(page.text.encode(encoding=how_encoding),'html.parser')

    dd_list = soup.find_all(tag_name)

    download_list = []

    title_list = []

    for dd in dd_list:
        if dd.a:
            if dd.a.has_attr('href'):
                download_list.append(top_url + dd.a['href'])
                title_list.append(dd.get_text())
    return download_list,title_list

def get_context(download_list,title_list,how_encoding,file_name):
    file = open(file_name, 'wb+')
    for x in range(0,len(download_list)) :
        try:
            time.sleep(0.5)
            print('downloading %s from %s'%(title_list[x],download_list[x]),end='')

            page = session.get(str(download_list[x]).strip(), headers=header)

            soup = BeautifulSoup(page.text.encode(encoding=how_encoding), 'html.parser')

            id_list = soup.find_all('div', {'id': 'chapterContent'})

            for id in id_list:
                context = id.get_text() + '\n\n'
                file.write(str(context).encode())
                print('[OK]',end='\n')
        except:
            print('[FAILED]', end='\n')
            continue

    file.close()

if __name__ == '__main__':
    how_encoding = 'ISO-8859-1'

    home_url = 'http://www.XXXX.com/html/229/229861/0.shtml'

    top_url = 'http://www.XXXX.com'

    '''
        top_url:��վ��Ŀ¼
        home_url:�½��б�Ŀ¼
        how_encoding:���뷽ʽ
        tag_name:�ڵ�����
    '''
    download_list,title_list = get_download_list(top_url,home_url,how_encoding,'dd')

    '''
            top_url:��վ��Ŀ¼
            home_url:�½��б�Ŀ¼
            how_encoding:���뷽ʽ
            tag_name:�����ļ�����
        '''
    get_context(download_list,title_list,how_encoding,'novel.txt')