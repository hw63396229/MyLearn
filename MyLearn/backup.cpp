#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

#include <fcntl.h>
#include <io.h>
#include <thread>
#include <functional>

#include <Windows.h>
#include <tchar.h>
#include <assert.h>
#include "Test.h"
#include "DLLtest.h"

#include <curl/curl.h>

void output(int i)
{
	std::cout << i << std::endl;
}

double eval(std::function<double(double)> f, double x = 2.0) { return f(x); }

//int main()
//{	
//	_setmode(_fileno(stdin), O_BINARY);
//	_setmode(_fileno(stdout), O_BINARY);
//	_setmode(_fileno(stderr), O_BINARY);	
//
//	char cBuffer[65536] = { 0 };
//	while (true)
//	{
//		unsigned int uiSize = 0;
//		std::cin.read((char*)&uiSize, sizeof(unsigned int));
//		uiSize = 6;
//		if (uiSize != 0 && uiSize < 65536)
//		{
//			memset(cBuffer, 0, 65536);
//			std::cin.read(cBuffer, uiSize);
//			
//			std::string strIn(cBuffer);
//			std::ofstream myfile;
//			myfile.open("example.txt", std::ios::app);
//			myfile << "Writing this to a file.\n";
//			myfile << "input size : " << uiSize << std::endl;
//			myfile << strIn << std::endl;
//			//////
//			int a = 2, b = 3;
//			HINSTANCE hDll = LoadLibrary(_T("DLLtest.dll"));
//			if (hDll == NULL)
//			{
//				myfile << "Load Dll Failed !" << std::endl;				
//			}
//			else
//			{
//				pAddFunc addFun = (pAddFunc)GetProcAddress(hDll, "add");
//				pPrintFunc  printFun = (pPrintFunc)GetProcAddress(hDll, "print");
//				myfile << addFun(a, b) << std::endl;
//			}			
//			FreeLibrary(hDll);
//			//myfile << printFun() << std::endl;
//			//////
//			myfile.close();
//
//			std::string strOut = "{\"result\":\"This is a Test\"}";
//			uiSize = strOut.length();
//
//			std::cout << char(((uiSize >> 0) & 0xFF));
//			std::cout << char(((uiSize >> 8) & 0xFF));
//			std::cout << char(((uiSize >> 16) & 0xFF));
//			std::cout << char(((uiSize >> 24) & 0xFF));
//			std::cout << strOut.c_str();
//		}
//		else
//			break;
//
//	}
//
//	/*std::ofstream fout("D:\\markdata.txt", std::ios::app);
//
//	std::ifstream  fin("u_4.mark", std::ios::binary);
//	char buf[16];
//	fin.read(buf, 16);
//
//	float num[4];
//	for (unsigned i = 0; i < 4; i++)
//	{
//		((char*)(&num[i]))[0] = buf[i * 4 + 0];
//		((char*)(&num[i]))[1] = buf[i * 4 + 1];
//		((char*)(&num[i]))[2] = buf[i * 4 + 2];
//		((char*)(&num[i]))[3] = buf[i * 4 + 3];
//		fout << num[i] << "  ";
//	}
//	fout << "angle: " << num[3] * 180.f / 3.1415926f + 720.f;
//	fout << std::endl;
//	fout.close();*/
//
//	/*std::function<double(double)>  f0    =     [](double x) { return 1; };
//	auto                           f1    =     [](double x) { return x; };
//	decltype(f0)                   fa[3] =     { f0, f1, [](double x) { return x * x; } };
//	std::vector<decltype(f0)>      fv    =     { f0, f1 };
//	fv.push_back([](double x)                  { return x * x; });
//
//	for (unsigned i = 0; i < fv.size(); i++)             { std::cout << fv[i](2.0) ; }
//	std::cout << std::endl;
//	for (unsigned i = 0; i < 3; i++)                     { std::cout << fa[i](2.0) ; }
//	std::cout << std::endl;
//	for (auto &f : fv)                                   { std::cout << f(2.0)  ; }
//	std::cout << std::endl;
//	for (auto &f : fa)                                   { std::cout << f(2.0) ; }
//	std::cout << std::endl;
//	std::cout << eval(f0) ;
//	std::cout << std::endl;
//	std::cout << eval(f1) << std::endl;*/
//	
//	/*Test  tt;
//	tt.SetTemp(100);
//
//	std::thread  t1(&Test::MyThread1, &tt);
//	std::thread  t2(&Test::MyThread2, &tt);
//	std::thread  t3(&Test::MyThread3, &tt);
//	t1.detach();
//	t2.detach();
//	t3.detach();
//	
//	std::cout << "Main thread !" << std::endl;*/
//
//
//	system("pause");
//}


void fun1()
{
	for (unsigned i = 0; i < 10; i++)
	{
		std::cout << "thread 1: " << i << std::endl;
	}
}
void fun2()
{
	for (unsigned i = 100; i < 110; i++)
	{
		std::cout << "thread 2: " << i << std::endl;
	}
}

template<typename T>
struct vec3
{
	T x;
	T y;
	T z;
};

template<typename T>
struct vec2
{
	T x;
	T y;
};

struct DicomElem
{
	short int group_tag;
	short int element_tag;
	char VR[2];
	int length;
	std::string data;
};
//OB OW OF UT SQ UN
bool getReserveFlag(short int VR)
{
	switch (VR)
	{
	case 0x424f:
		return true;        //"OB"
	case 0x574f:
		return true;        //"OW"
	case 0x464f:
		return true;        //"OF"
	case 0x5455:
		return true;        //"UT"
	case 0x5153:
		return true;        //"SQ"
	case 0x4e55:
		return true;        //"UN"

	default:
		return false;
	}	
}

//dicom test
//int main()
//{
//	//const int a = 1;
//	//int b = 5;
//	////int c = add();
//	//auto s = [a]()mutable { return a; };
//
//	std::ifstream  in("C:\\Users\\share\\Desktop\\Franklin_Benjamin[2018-01-22_16-28-59].dcm", std::ios::binary);
//	std::streampos   pos = in.tellg();     //   save   current   position   
//	in.seekg(0, std::ios::end);
//	int fileLen = static_cast<int>(in.tellg());
//	in.seekg(pos);     //   restore   saved   position   
//
//	std::vector<DicomElem>   m_vElement;
//	DicomElem temp;
//	std::string str("DICM");
//
//	char head[128];
//	in.read(head, 128);
//	
//	char dicm[4];
//	in.read(dicm, 4);
//	std::string valueStr(dicm);
//	if ((valueStr == str) == 0)
//	{
//		char tag[4];
//		while (in.peek() != EOF)//!in.eof())
//		{
//			in.read(tag, 2);                       //组号
//			temp.group_tag = *(short int*)tag;
//			in.read(tag, 2);                       //元素号
//			temp.element_tag = *(short int*)tag;
//
//			in.read(temp.VR, 2);                       //VR
//			short int reserveValue = *(short int*)temp.VR;
//			bool reserveFlag = getReserveFlag(reserveValue);
//			if (reserveFlag)
//			{
//				in.read(tag, 2);                  //VR为OB OW OF UT SQ UN的元素结构预留2字节
//				in.read(tag, 4);                     //size
//				temp.length = *(int*)tag;
//			}
//			else 
//			{
//				in.read(tag, 2);                     //size
//				temp.length = *(short int*)tag;
//			}
//
//			temp.data.resize(temp.length);
//			in.read(&temp.data[0], temp.length);
//
//			m_vElement.push_back(temp);
//		}
//	}
//
//	//解析0009组号的内容
//	std::vector<DicomElem>    m_v0009Value(8 * 3);
//	DicomElem  temp9;
//	char* data9 = &m_vElement[31].data[0];
//	int dataLen = m_vElement[31].length;
//	char tag9[4];
//	unsigned len = 0;
//	unsigned i = 0;
//	while (dataLen != len)
//	{
//		len += 8;
//		for (unsigned k = 0; k < 3; k++)
//		{
//			DicomElem &temp9 = m_v0009Value[i];
//
//			memcpy_s(tag9, 2, &data9[len], 2);               //组号
//			temp9.group_tag = *(short int*)tag9;
//			len += 2;
//
//			memcpy_s(tag9, 2, &data9[len], 2);              //元素号
//			temp9.element_tag = *(short int*)tag9;
//			len += 2;
//
//			memcpy_s(temp9.VR, 2, &data9[len], 2);        //VR
//			len += 2;
//			short int reserveValue = *(short int*)temp9.VR;
//			bool reserveFlag = getReserveFlag(reserveValue);
//			if (reserveFlag)
//			{
//				memcpy_s(tag9, 2, &data9[len], 2);
//				len += 2;
//				memcpy_s(tag9, 4, &data9[len], 4);
//				temp9.length = *(int*)tag9;
//				len += 4;
//			}
//			else
//			{
//				memcpy_s(tag9, 2, &data9[len], 2);
//				temp9.length = *(short int*)tag9;
//				len += 2;
//			}
//
//			temp9.data.resize(temp9.length);
//			memcpy_s(&temp9.data[0], temp9.length, &data9[len], temp9.length);
//			len += temp9.length;
//
//			//m_v0009Value.push_back(temp9);
//			i++;
//		}
//	}
//
//	//解析ply文件内容 11 17
//	char* data11 = &m_v0009Value[11].data[0];
//	int len11 = m_v0009Value[11].length;
//	for (unsigned i = 0; i < 333; i++)
//	{
//		std::cout << data11[i];
//	}
//	unsigned  vNum = 0, sNum = 0, startPos = 0;;
//	while (startPos == 0)
//	{
//		std::string str;
//		for (int i = 0; i < len11; i++)
//		{
//			if (data11[i] != ' ' && data11[i] != '\n' && data11[i] != '\t')
//			{
//				str.push_back(data11[i]);
//
//				if (str == "vertex" && data11[i + 1] == ' ')   //从头中取出顶点个数
//				{
//					str = "";
//					for (int j = i + 1; j < len11; j++)
//					{
//						if (data11[j] != '\n' && data11[j] != ' ')
//							str.push_back(data11[j]);
//						else if (data11[j] == '\n')
//						{
//							vNum = std::atoi(str.c_str());
//							str = "";
//							break;
//						}
//					}
//				}
//				else if (str == "face")    //从头中取出面片个数
//				{
//					str = "";
//					for (int j = i + 1; j < len11; j++)
//					{
//						if (data11[j] != '\n' && data11[j] != ' ')
//							str.push_back(data11[j]);
//						else if (data11[j] == '\n')
//						{
//							sNum = std::atoi(str.c_str());
//							str = "";
//							break;
//						}
//					}
//				}
//				else if (str == "end_header")
//				{
//					str = "";
//					startPos = i + 2;
//					break;
//				}
//			}
//			else
//				str = "";
//		}
//	}
//
//	std::vector<vec3<float>> m_vVert(vNum);
//	std::vector<vec2<float>> m_vTexture(vNum);
//	std::vector<vec3<int>>   m_vTriangle(sNum);
//	unsigned vlen = vNum * sizeof(float) * 5 + startPos;
//	char value[4];
//	for (unsigned i = 0; i < vNum; i++)
//	{
//		unsigned tlen = startPos + i * sizeof(float) * 5;
//		memcpy_s(value, 4, &data11[tlen], 4);
//		m_vVert[i].x = *(float*)value;
//
//		memcpy_s(value, 4, &data11[tlen + 4], 4);
//		m_vVert[i].y = *(float*)value;
//
//		memcpy_s(value, 4, &data11[tlen + 8], 4);
//		m_vVert[i].z = *(float*)value;
//
//		memcpy_s(value, 4, &data11[tlen + 12], 4);
//		m_vTexture[i].x = *(float*)value;
//
//		memcpy_s(value, 4, &data11[tlen + 16], 4);
//		m_vTexture[i].y = *(float*)value;
//	}
//
//	startPos = vlen;
//	for (unsigned i = 0; i < sNum; i++)
//	{
//		unsigned tlen = startPos + i * sizeof(int) * 3 + (i + 1);
//
//		memcpy_s(value, 1, &data11[tlen - 1], 1);
//		unsigned char tp = *(unsigned char*)value;
//
//		memcpy_s(value, 4, &data11[tlen + 0], 4);         //忽略第一个数字
//		m_vTriangle[i].x = *(int*)value;
//
//		memcpy_s(value, 4, &data11[tlen + 4], 4);
//		m_vTriangle[i].y = *(int*)value;
//
//		memcpy_s(value, 4, &data11[tlen + 8], 4);
//		m_vTriangle[i].z = *(int*)value;
//	}
//
//	std::ofstream fp("C:\\Users\\share\\Desktop\\gm.obj");
//	for (unsigned i = 0; i < vNum; i++)
//	{
//		fp << "v " << m_vVert[i].x << " " << m_vVert[i].y << " " << m_vVert[i].z << std::endl;
//	}
//	for (unsigned i = 0; i < sNum; i++)
//	{
//		fp << "f " << m_vTriangle[i].x + 1 << " " << m_vTriangle[i].y + 1 << " " << m_vTriangle[i].z + 1 << std::endl;
//	}
//	fp.close();
//
//	system("pause");
//}

//curl test

size_t call_wirte_func(const char *ptr, size_t size, size_t nmemb, std::string *stream)
{
	assert(stream != NULL);
	size_t len = size * nmemb;
	stream->append(ptr, len);
	return len;
}
// 返回http header回调函数    
size_t header_callback(const char  *ptr, size_t size, size_t nmemb, std::string *stream)
{
	assert(stream != NULL);
	size_t len = size * nmemb;
	stream->append(ptr, len);
	return len;
}
#define SKIP_PEER_VERIFICATION
int main(int argc, char* argv[])
{
	CURL *curl;
	CURLcode code;
	std::string szbuffer;
	std::string szheader_buffer;
	char errorBuffer[CURL_ERROR_SIZE];
	std::string url = "https://webhook.site/e8937752-14e8-4d38-8320-b9ed4cb1b8c1";
	//std::string url = "https://vip.icbc.com.cn/icbc/perbank/index.jsp";  
	std::string useragent = "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:13.0) Gecko/20100101 Firefox/13.0.1";
	/*
	CURL_GLOBAL_ALL                //初始化所有的可能的调用。
	CURL_GLOBAL_SSL               //初始化支持 安全套接字层。
	CURL_GLOBAL_WIN32            //初始化win32套接字库。
	CURL_GLOBAL_NOTHING         //没有额外的初始化。
	*/
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {

		struct curl_slist *headers = NULL;
		//Appends a string to a linked list.If no list exists, it will be created
		//first.Returns the new list, after appending.
		headers = curl_slist_append(headers, "Accept:application/json, text/plain");
		headers = curl_slist_append(headers, "Content-Type:application/json");
		headers = curl_slist_append(headers, "Accept-Charset:utf-8");
		headers = curl_slist_append(headers, "Accept-Encoding:gzip");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "POST VALUE");

		// 远程URL，支持 http, https, ftp  
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		//curl_easy_setopt(curl, CURLOPT_USERAGENT, useragent.c_str());
		// 官方下载的DLL并不支持GZIP，Accept-Encoding:deflate, gzip  
		//curl_easy_setopt(curl, CURLOPT_ENCODING, "gzip, deflate");
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);//调试信息打开  

		//设置发送超时时间  
		//code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1000);

		//https 访问专用：start  
#ifdef SKIP_PEER_VERIFICATION  
		//跳过服务器SSL验证，不使用CA证书  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		//如果不跳过SSL验证，则可指定一个CA证书目录  
		//curl_easy_setopt(curl, CURLOPT_CAPATH, "this is ca ceat");  
#endif  

#ifdef SKIP_HOSTNAME_VERFICATION  
		//验证服务器端发送的证书，默认是 2(高)，1（中），0（禁用）  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif  
		//https 访问专用：end  


		//发送cookie值给服务器  
		//curl_easy_setopt(curl, CURLOPT_COOKIE, "name1=var1; name2=var2;");   
		/* 与服务器通信交互cookie，默认在内存中，可以是不存在磁盘中的文件或留空 */
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookie.txt");
		/* 与多个CURL或浏览器交互cookie，会在释放内存后写入磁盘文件 */
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./cookie.txt");

		/* POST 数据 */
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "POST VALUE");  
		//设置重定向的最大次数  
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);
		//设置301、302跳转跟随location  
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		//抓取内容后，回调函数  
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_wirte_func);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);
		//抓取头信息，回调函数  
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);

		/*
		CURLE_OK    任务完成一切都好
		CURLE_UNSUPPORTED_PROTOCOL  不支持的协议，由URL的头部指定
		CURLE_COULDNT_CONNECT   不能连接到remote 主机或者代理
		CURLE_REMOTE_ACCESS_DENIED  访问被拒绝
		CURLE_HTTP_RETURNED_ERROR   Http返回错误
		CURLE_READ_ERROR    读本地文件错误
		CURLE_SSL_CACERT    访问HTTPS时需要CA证书路径
		*/
		code = curl_easy_perform(curl);
		//turn a CURLcode value into the equivalent human readable error string
		const char* ch;
		ch = curl_easy_strerror(code);
		std::string str;
		str = ch;
		if (CURLE_OK == code) {
			double val;

			std::cout << szheader_buffer << std::endl;
			/* check for bytes downloaded */
			code = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &val);
			if ((CURLE_OK == code) && (val>0))
				printf("Data downloaded: %0.0f bytes.\n", val);

			/* check for total download time */
			code = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &val);
			if ((CURLE_OK == code) && (val>0))
				printf("Total download time: %0.3f sec.\n", val);

			/* check for average download speed */
			code = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &val);
			if ((CURLE_OK == code) && (val>0))
				printf("Average download speed: %0.3f kbyte/sec.\n", val / 1024);

			printf("%s\n", szbuffer.c_str());
		}
		else {
			fprintf(stderr, "Failed to get '%s' [%s]\n", url, errorBuffer);
			// exit(EXIT_FAILURE);  
		}

		/* 释放内存 */
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	getchar();
	return 0;
}

//int main()
//{
//	CURL *curl;
//	CURLcode res;
//
//	curl = curl_easy_init();
//
//	if (curl)
//	{
//		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
//		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
//		//curl_easy_setopt(curl, CURLOPT_URL, "https://mail.qq.com");
//		//curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.2.201:6008");
//		curl_easy_setopt(curl, CURLOPT_URL, "https://webhook.site/#/e8937752-14e8-4d38-8320-b9ed4cb1b8c1");
//
//		/* example.com is redirected, so we tell libcurl to follow redirection */
//		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//
//		/* Perform the request, res will get the return code */
//		res = curl_easy_perform(curl);
//
//		/* Check for errors */
//		if (res != CURLE_OK)
//			fprintf(stderr, "curl_easy_perform() failed: %s\n",
//				curl_easy_strerror(res));
//
//		/* always cleanup */
//		curl_easy_cleanup(curl);
//
//	}
//
//	system("pause");
//	return 0;
//}

//dicom test
//#include <dcmtk\dcmdata\dctk.h>
//#include <DCMTK\dcmimgle\dcmimage.h>
//#pragma comment(linker,"/NOD:LIBCMT")
//#pragma comment(lib, "wsock32.lib")
//#pragma comment(lib, "netapi32.lib")
//#pragma comment(lib, "ofstd.lib")
//#pragma comment(lib, "oflog.lib")
//#pragma comment(lib, "dcmdata.lib")
//#pragma comment(lib, "Iphlpapi.lib")
//
////#pragma comment(lib, "dcmnet.lib")
////#pragma comment(lib, "dcmwlm.lib")
////#pragma comment(lib, "dcmtls.lib")
////#pragma comment(lib, "dcmqrdb.lib")
////#pragma comment(lib, "dcmdsig.lib")
////#pragma comment(lib, "dcmsr.lib")
////#pragma comment(lib, "dcmpstat.lib")
////#pragma comment(lib, "dcmimage.lib")
//
//#pragma comment(lib, "zlib.lib")
//
//
//int main(int argc, char* argv[])
//{
//	char uid[100];
//	DcmFileFormat fileformat;
//	DcmMetaInfo *metainfo = fileformat.getMetaInfo();
//	DcmDataset *dataset = fileformat.getDataset();
//
//	//***meta group******/
//	metainfo->putAndInsertString(DCM_FileMetaInformationVersion, "us test dcm file");
//	metainfo->putAndInsertString(DCM_MediaStorageSOPClassUID, UID_RETIRED_UltrasoundImageStorage);
//	metainfo->putAndInsertString(DCM_MediaStorageSOPInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
//	metainfo->putAndInsertString(DCM_TransferSyntaxUID, UID_LittleEndianExplicitTransferSyntax);
//	metainfo->putAndInsertString(DCM_ImplementationClassUID, "999.999");
//
//	//***identifying group****/
//	dataset->putAndInsertString(DCM_ImageType, "ORIGINAL\\PRIMARY\\TEE\\0011");
//	dataset->putAndInsertString(DCM_SOPClassUID, UID_RETIRED_UltrasoundImageStorage);//UID_SecondaryCaptureImageStorage);
//	dataset->putAndInsertString(DCM_SOPInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
//	dataset->putAndInsertString(DCM_StudyID, "398474");
//	dataset->putAndInsertString(DCM_StudyDate, "20100823");
//	dataset->putAndInsertString(DCM_StudyTime, "080322");
//	dataset->putAndInsertString(DCM_Modality, "US");//OT
//
//	dataset->putAndInsertString(DCM_Manufacturer, "ACME product");
//	dataset->putAndInsertString(DCM_ReferringPhysicianName, "ANONY");
//	dataset->putAndInsertString(DCM_StudyDescription, "STUDY description");
//	dataset->putAndInsertString(DCM_SeriesDescription, "SERIES DESCRIPTION");
//	dataset->putAndInsertString(DCM_StageNumber, "1");
//	dataset->putAndInsertString(DCM_NumberOfStages, "1");
//	dataset->putAndInsertString(DCM_ViewNumber, "1");
//	dataset->putAndInsertString(DCM_NumberOfViewsInStage, "1");
//	/***patient group*****/
//	dataset->putAndInsertString(DCM_PatientID, "PatientID");
//	dataset->putAndInsertString(DCM_PatientName, "PatientName");
//	dataset->putAndInsertString(DCM_PatientSex, "M");
//	dataset->putAndInsertString(DCM_PatientBirthDate, "20000302");
//
//	/************************************************************************/
//	/* acquisiton group                                                                     */
//	/************************************************************************/
//	//DCM_ProtocolName
//	/************************************************************************/
//	/* relation group                                                                      */
//	/************************************************************************/
//	dataset->putAndInsertString(DCM_StudyInstanceUID, "999.999.2.19941105.112000");
//	dataset->putAndInsertString(DCM_SeriesInstanceUID, "999.999.2.19941105.112000.2");
//	dataset->putAndInsertString(DCM_SeriesNumber, "2");
//	dataset->putAndInsertString(DCM_AccessionNumber, "1");
//	//dataset->putAndInsertString(DCM_InstanceNumber,);
//
//	//调窗
//	//dataset->putAndInsertString(DCM_WindowCenter, "256");
//	//dataset->putAndInsertString(DCM_WindowWidth, "128");
//
//	const int width = 256;
//	const int height = 256;
//	dataset->putAndInsertString(DCM_InstanceNumber, "1");
//	//dataset->putAndInsertString(DCM_PatientOrientation,"HFL");
//	dataset->putAndInsertString(DCM_PhotometricInterpretation, "RGB");
//	dataset->putAndInsertUint16(DCM_SamplesPerPixel, 3);
//	dataset->putAndInsertUint16(DCM_BitsAllocated, 8);
//	dataset->putAndInsertUint16(DCM_BitsStored, 8);
//	dataset->putAndInsertUint16(DCM_HighBit, 7);
//	dataset->putAndInsertUint16(DCM_PixelRepresentation, 0);
//	dataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);
//	dataset->putAndInsertString(DCM_PixelAspectRatio, "4\\3");
//	dataset->putAndInsertUint16(DCM_Rows, height);//
//	dataset->putAndInsertUint16(DCM_Columns, width);//
//
//
//	BYTE* pData = new BYTE[width*height * 3];
//	memset(pData, 0, width*height * 3);
//	for (int y = 0; y < height; y++) {
//		//memset(pData+ y*width*3, y & 0xff0000,width*3);
//		for (int x = 0; x<width * 3; x++)
//		{
//			if (x % 3 == 0)
//				pData[y*width * 3 + x] = 0xff;
//			else
//				pData[y*width * 3 + x] = rand() % 256;
//		}
//	}
//	dataset->putAndInsertUint8Array(DCM_PixelData, pData, width*height * 3);
//	delete[] pData;
//	OFCondition status = fileformat.saveFile("d:\\test.dcm",
//		EXS_LittleEndianImplicit, EET_UndefinedLength, EGL_withoutGL);
//	if (status.bad())
//	{
//		printf("\n cannot write dicom file");
//		return false;
//	}
//	return true;
//}

std::wstring UTF8ToUnicode(const std::string &str)
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t   *pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	std::wstring  rt;
	rt = (wchar_t *)pUnicode;
	delete  pUnicode;

	return  rt;
}