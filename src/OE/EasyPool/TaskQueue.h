/**
* @author : ��³��
* @date   : 2017��04��
* @version: 1.0
* @note   : ���� Apache ����֤ 2.0 �棨���¼�ơ�����֤������Ȩ;
*           �������ر����ɣ�����������ʹ������ļ���
* @remarks: �����Ի�ø����ɵĸ�����
*           http://www.apache.org/licenses/LICENSE-2.0
*           �������÷�����Ҫ��������ͬ�⣬�������ɷַ�������
*           Ҫ����ԭ�����ַ���û���κ���ʽ�ģ���ȷ�������ĵ������
*           �μ����ձ����ɿ�������Ȩ�޼����Ƶ��ض����Ե�����֤��
*
*   ����Ի�øô�������°汾��
*
*        http://git.oschina.net/Mr_ChenLuYong/oeasypool
*
*   ��Դ�����������˶��ڴ�����Ĺ�ͬά����
*
*
*   ��������Щ���뻹�в�����ĵط�����ͨ�����µ����½���ѧϰ��
*
*        ���͵�ַ��http://blog.csdn.net/csnd_ayo
*
*        ���µ�ַ��http://blog.csdn.net/csnd_ayo/article/details/72457190
*
* 	 �ڴ����ύBug����ӭIssues��
*
*/


#ifndef __OETASKQUEUE_H__
#define __OETASKQUEUE_H__

#include <deque>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <memory>

#include "Task.h"

/// ���������
class OETaskQueue
{
public:
	OETaskQueue();
	~OETaskQueue();

private:
	/// �����������
	std::deque<std::shared_ptr<OETask> > queue_;
	/// ��������map
	std::unordered_map<int, std::shared_ptr<OETask>> mapDoingTask_;
	/// ������
	std::mutex mutex_;
	/// ��������
	std::condition_variable conditPut_;

public:
	/**
	* @brief ������е�ĩβ��������
	* @param ��task ������
	*/
	void put_back(std::shared_ptr<OETask> task);
	/**
	* @brief ������е�ͷ����������
	* @param ��task ������
	*/
	void put_front(std::shared_ptr<OETask> task);
	/**
	* @brief ����ȡ���ף���������ӵ����������б��У�
	* @return��������
	*/
	std::shared_ptr<OETask> get(void);
	/**
	* @brief ����ȡ����˫�������Ĵ�С
	* @return����С
	*/
	size_t size(void);

	/**
	* @brief ���ͷŶ���
	*/
	void release(void);
	/**
	* @brief ��ɾ�����񣨴Ӿ�������ɾ���������������û�У���ִ�ж�����û�У��еĻ�����ȡ��״̬λ��
	* @param ��nID ����ı��
	* @return���ɹ�����0 ʧ�ܷ��ط�0
	*/
	int deleteTask(int nID);
	/**
	* @brief ��ɾ����������
	* @return���ɹ�����0 ʧ�ܷ��ط�0
	*/
	int deleteAllTasks(void);
	/**
	* @brief ��������ɻص����������б���ɾ��ָ������
	* @param ��nID ����ı��
	* @return���ɹ�����0 ʧ�ܷ��ط�0
	*/
	int onTaskFinished(int nID);
	/**
	* @brief ���ж������Ƿ�ִ�����
	* @param ��nID ����ı��
	* @return��������
	*/
    std::shared_ptr<OETask> isTaskProcessed(int nId);

	/**
	* @brief ���ȴ������񵽴����ʱ����ʱ�Զ����ѣ�
	* @param ��millsec ��ʱʱ�䣨���룩
	* @return���ɹ�����true ʧ�ܷ���false
	*/
	bool wait(std::chrono::milliseconds millsec);

};

#endif // __OETASKQUEUE_H__