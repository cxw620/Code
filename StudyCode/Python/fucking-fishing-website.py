# coding:utf-8
# V3.0.20211113
# test git
import random
import string
import json
import requests
import time
from fake_useragent import UserAgent
from requests import exceptions

proxyAPIurl = "http://api.xdaili.cn/xdaili-api//greatRecharge/getGreatIp?spiderId=cd91eff7cca94ff3a60ed1ac9663c324&orderno=YZ202111137646oJKClM&returnType=2&count="
url_to_fuck = "http://sdx.asdsasad.cn/2018.php"
desire_fuck_total = 30000
ua = UserAgent()


def tips(data: list, add_data_list=[], add_data={}):
    # 自己设计的日志输出V2.0.20211113
    try:
        if data[0] == 0:
            # 这是一般类型，默认输出格式：【INFO】时间串 内容
            typeString = "[INFO]"
        else:
            # 这是警告类型，默认输出格式：【INFO】时间串 内容
            typeString = "[WARN]"
        dataString = str(data[1])
        if add_data_list:
            if len(add_data_list) == len(add_data):
                for i in range(0, len(add_data_list)):
                    dataString = (
                        dataString
                        + "|"
                        + str(add_data_list[i])
                        + str(add_data[str(add_data_list[i])])
                    )
    except:
        typeString = "[ERROR]"
        dataString = "致命错误！"
    finally:
        timeString = str(time.strftime("%Y-%m-%d %H:%M:%S %Z", time.localtime()))
        print(typeString, timeString, dataString)


def proxyGet(ip_need_count):
    ip_list = []
    url = str(proxyAPIurl + str(ip_need_count))
    repJSON = json.loads(requests.get(url).text)
    if repJSON["ERRORCODE"] == "0" and repJSON["RESULT"]:
        for i in range(0, ip_need_count, 1):
            ip_list.append(
                {
                    "http": str(
                        "http://"
                        + repJSON["RESULT"][i]["ip"]
                        + ":"
                        + repJSON["RESULT"][i]["port"]
                    )
                }
            )
        tips([0, ip_list])
        return ip_list
    else:
        return ip_list


def fuck(proxyParam):
    # 生成随机QQ号和QQ密码
    qqID = str(int(random.randint(300000, 4000000000)))
    qqPwd = (
        "".join(random.sample(string.ascii_uppercase, 1))
        + "".join(random.sample(string.ascii_lowercase, random.randint(1, 2)))
        + "".join(random.sample(string.punctuation, 1))
        + "".join(random.sample(string.digits, random.randint(6, 9)))
    )
    payload = {"u": qqID, "p": qqPwd, "user": "ff"}
    uaString = ua.random
    headers = {"User-Agent": uaString}
    try:
        r = requests.post(
            url_to_fuck, data=payload, timeout=3, headers=headers, proxies=proxyParam
        )
        req_status = str(r.status_code)
        req_time = str(r.elapsed.total_seconds())
        return req_status, req_time
    except exceptions.Timeout as e:
        req_status = str(e)
        req_time = "0"
        return req_status, req_time
    except:
        req_status = "999"
        req_time = "0"
        return req_status, req_time


def main(desire_fuck_total):
    ip_list_rec = []
    ip_list = proxyGet(20)
    if not ip_list:
        tips([1, "获取代理ip失败！"])
        exit(1)
    for i in range(20):
        ip_list_rec.append([0, ip_list[i]])

    for i in range(1, desire_fuck_total, 1):
        ipSelect = random.randint(0, len(ip_list) - 1)

        req = fuck(ip_list[ipSelect])
        req_status = req[0]
        req_time = req[1]

        if req_status == "200":
            tips(
                [0, "请求成功！"],
                ["本次请求次序是：", "还有", "次", "用时（秒）："],
                {"本次请求次序是：": i, "还有": desire_fuck_total, "次": "", "用时（秒）：": req_time},
            )
        else:
            desire_fuck_total += 1
            ip_list_rec[ipSelect][0] += 1
            if ip_list_rec[ipSelect][0] > 10:
                del ip_list_rec[ipSelect]
                del ip_list[ipSelect]
            tips(
                [1, "请求失败！总次数加一！"],
                ["ERROR", "本次请求次序是：", "还有", "次"],
                {"ERROR": req_status, "本次请求次序是：": i, "还有": desire_fuck_total, "次": ""},
            )

    tips([0, "ALL DONE"])


if __name__ == "__main__":
    main(desire_fuck_total)
