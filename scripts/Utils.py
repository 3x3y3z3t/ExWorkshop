#
import os
import requests
import sys
import time
import urllib
import winreg

from zipfile import ZipFile

def GetSystemEnvironmentVariable(_name):
    key = winreg.CreateKey(winreg.HKEY_LOCAL_MACHINE, r"System\CurrentControlSet\Control\Session Manager\Environment")
    try:
        return winreg.QueryValueEx(key, _name)[0]
    except:
        return None

def GetUserEnvironmentVariable(_name):
    key = winreg.CreateKey(winreg.HKEY_CURRENT_USER, r"Environment")
    try:
        return winreg.QueryValueEx(key, _name)[0]
    except:
        return None


def DownloadFile(_url, _filepath):
    path = _filepath #cache filepath
    _filepath = os.path.abspath(_filepath)
    os.makedirs(os.path.dirname(_filepath), exist_ok = True)

    if type(_url) is list:
        for url_option in _url:
            print("Downloading ", url_option)
            try:
                DownloadFile(url_option, _filepath)
                return
            except urllib.error.URLError as _e:
                print(f"URL Error: {_e.reason}, proceeds with backup..\n\n")
                os.remove(_filepath)
                pass
            except urllib.error.HTTPError as _e:
                print(f"HTTP Error: {_e.code}, proceeds with backup..\n\n")
                os.remove(_filepath)
                pass
            except:
                print(f"Error, proceeds with backup..\n\n")
                os.remove(_filepath)
                pass

        raise ValueError(f"Failed to download {_filepath}")

    if type(_url) is str:
        with open(_filepath, 'wb') as file: # same as using(...)
            headers = {'User-Agent': "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36"}
            response = requests.get(_url, headers = headers, stream = True)
            total = response.headers.get('content-length')

            if total is None:
                file.write(response.content)
            else:
                downloaded = 0
                total = int(total)
                startTime = time.time()

                for data in response.iter_content(chunk_size = max(int(total/1000), 1024 * 1024)):
                    downloaded += len(data)
                    file.write(data)

                    if total != 0 and downloaded < total:
                        done = int(50 * downloaded / total)
                        percentage = (downloaded / total * 100)
                    else:
                        done = 50
                        percentage = 100

                    elapsedTime = time.time() - startTime
                    avgKBPerSec = 0.0
                    if elapsedTime != 0:
                       avgKbPerSec = downloaded / 1024 / elapsedTime

                    avgSpeedString = ""
                    if avgKBPerSec > 1024 * 1024:
                        avgSpeedString = '{:.2f} GB/s'.format(avgKBPerSec / (1024 * 1024))
                    elif avgKBPerSec > 1024:
                        avgSpeedString = '{:.2f} MB/s'.format(avgKBPerSec / 1024)
                    else:
                        avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSec)

                    sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format('█' * done, '.' * (50 - done), percentage, avgSpeedString))
                    sys.stdout.flush()

        sys.stdout.write('\n');
        return

    raise TypeError("Argument '_url' must be of type List or String")

def UnzipFile(_filepath, _deleteZipFile = True):
    zipFilePath = os.path.abspath(_filepath)
    zipFileDirname = os.path.dirname(zipFilePath)
    zipFileContent = dict()
    zipFileContentSize = 0

    with ZipFile(zipFilePath, 'r') as zipFileFolder:
        for name in zipFileFolder.namelist():
            zipFileContent[name] = zipFileFolder.getinfo(name).file_size
        zipFileContentSize = sum(zipFileContent.values())

        extractedContentSize = 0
        startTime = time.time()
        for zippedFileName, zippedFileSize in zipFileContent.items():
            unzippedFilePath = os.path.abspath(f"{zipFileDirname}/{zippedFileName}")
            os.makedirs(os.path.dirname(unzippedFilePath), exist_ok = True)
            if os.path.isfile(unzippedFilePath):
                zipFileContentSize -= zippedFileSize
            else:
                zipFileFolder.extract(zippedFileName, path = zipFileDirname, pwd = None)
                extractedContentSize += zippedFileSize

            done = 50
            percentage = 100
            if zipFileContentSize != 0:
                done = int(50 * extractedContentSize / zipFileContentSize)
                percentage = extractedContentSize / zipFileContentSize * 100
            
            elapsedTime = time.time() - startTime
            avgKBPerSec = 0.0
            if elapsedTime != 0:
                avgKBPerSec = extractedContentSize / 1024 / elapsedTime
                
            avgSpeedString = ""
            if avgKBPerSec > 1024 * 1024:
                avgSpeedString = '{:.2f} GB/s'.format(avgKBPerSec / (1024 * 1024))
            elif avgKBPerSec > 1024:
                avgSpeedString = '{:.2f} MB/s'.format(avgKBPerSec / 1024)
            else:
                avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSec)
                
            sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format('█' * done, '.' * (50 - done), percentage, avgSpeedString))
            sys.stdout.flush()

    sys.stdout.write('\n');

    if _deleteZipFile:
        os.remove(zipFilePath)
