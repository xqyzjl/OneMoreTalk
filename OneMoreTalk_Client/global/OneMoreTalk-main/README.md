# OneMoreTalk
NeuTalk base on Qt
小学期NeuTalk项目



# 需求分析：

*1.相关系统分析员向用户初步了解需求，然后用相关的工具软件列出要开发的系统的大功能模块，每个大功能模块有哪些小功能模块，对于有些需求比较明确相关的界面时，在这一步里面可以初步定义好少量的界面。*
*2.系统分析员深入了解和分析需求，根据自己的经验和需求用WORD或相关的工具再做出一份文档系统的功能需求文档。这次的文档会清楚列出系统大致的大功能模块，大功能模块有哪些小功能模块，并且还列出相关的界面和界面功能。*
*3.系统分析员向用户再次确认需求。*

## 功能设计：

### 1、登录注册系统：

* 登录
* 注册
* 找回密码
* *登陆状态*
* *手机验证*

### 2、主界面：

* 个人信息（头像、昵称、个性标签）
* 消息
* 好友
* 群聊
* 添加好友
* 添加群聊

### 3、基本信息：

* ID
* 头像
* 昵称
* 年龄
* 性别
* 密保问题
* 密保答案
* 个性标签

### 4、1对1聊天：

* 消息框

* 表情

* 代码

  ？气泡聊天？

### 5、群聊：

* @特定用户

# 概要设计：

*首先，开发者需要对软件系统进行概要设计，即系统设计。概要设计需要对软件系统的设计进行考虑，包括系统的基本处理流程、系统的组织结构、模块划分、功能分配、接口设计、运行设计、数据结构设计和出错处理设计等，为软件的详细设计提供基础。*

## 客户端：



## 服务端：

### 数据库表：

* usersInfo (userId INT PRIMARY KEY, Password TEXT, userName TEXT, userImg INT, userQ TEXT, userA TEXT, userLabel TEXT, userAge INT, userSex INT)

  // 昵称 - 头像编号 - 密保问题 - 密保答案 - 个性签名 - 年龄 - 性别（0女1男）

* friend+[userid] (friendId INT UNIQUE); // userid 好友

* group+[groupid] (userId INT UNIQUE);  // group 用户

* p2pmsg+[userid1]_[userid2] (TM time, senderId INT, Msg TEXT); // Id 为发送者 id

* groupmsg+[groupid] (TM time, senderId INT, Msg TEXT);  // Id 为发送者 id

### 数据库API：

* open :
  * bool openDatabase ();

* create：

  * bool createTableUserInfo(QString tablename); // userInfo

  * bool createTableFriend(int id); // friend & group
  * bool createTableGroup(int id); // group
  * bool createTableP2PMsg(int id1, int id2); // p2pmsg
  * bool createTableGroupMsg(int id); // groupmsg

* insert :

  * bool insertUsersInfo (int userid, QString password, QString username, int userImg, QString userq, QString usera, QString userlabel = "", int userage = 0, int usersex = 0);

  * bool insertUserFriend (int userid, int friendid);
  * bool insertGroupUser (int groupid, QList<int> userid);
  * bool insertP2PMsg (int senderid, int receiverid, QString tm, QString msg);
  * bool insertGroupMsg (int groupid, int senderid, QString tm, QString msg);

* select :

  * UserInfo selectUserInfo (int userid);
  * QList<UserInfo> selectFriendInfo(int userid);
  * SecreteInfo selectUserSecreteInfo (int userid);
  * QList<Message> selectP2PMsg (int senderid, int receiverid);
  * QList<Message> selectGroupMsg (int groupid);

* update :

  * void deleteUserInfo (int userid);
  * void deleteUserFriend(int userid, int friendid);
  * void deleteGroupUser(int groupid, QList<int> userid);

* drop :

  * void dropFriend (int userid, int friendid);
  * void dropGroup (int groupid);

* update :
  * updateUsersInfo(int userid, QString password, QString username, int userImg, QString userq, QString usera, QString userlabel, int userage, int usersex);



# 详细设计：

*在概要设计的基础上，开发者需要进行软件系统的详细设计。在详细设计中，描述实现具体模块所涉及到的主要算法、数据结构、类的层次结构及调用关系，需要说明软件系统各个层次中的每一个程序(每个模块或子程序)的设计考虑，以便进行编码和测试。应当保证软件的需求完全分配给整个软件。详细设计应当足够详细，能够根据详细设计报告进行编码。*

## 消息传输格式

### 登陆页面

- 注册请求：
  - 客户端上传：`"SIGNUP#[nickname]#[password]#[question]#[answer]"`
  - 服务端返回：`"SIGNUP_OK#[userID]"` / `"ERROR: SIGNUP_ERROR"`
- 登录请求：
  - 客户端上传：`"LOGIN#[userID]#[password]"`
  - 服务端返回：`"LOGIN_OK"` / `"ERROR: LOGIN_ERROR"`
- 找回密码：
  - 客户端上传：
    - `"PASSWORD_FIND#[userid]"`
    - `"PASSWORD_PROTECT_ANSWER#[answer]#[new password]"`
  - 服务端返回：
    - `"PASSWORD_PROTECT_QUESTION#[question]"`/`"ERROR: PASSWORD_FIND_USERID_ERROR"`
    - `"PASSWORD_FIND_OK"`/`"ERROR: PASSWORD_FIND_ANSWER_ERROR"`/`"ERROR: PASSWORD_FIND_SAME_ERROR"`

### 消息页面

- 客户端发送消息：
  - 客户端上传：`"MESSAGE#[senderID]#[userID/groupID]#[message]"`
  - 服务端返回:  `"SEND_OK"` / `"ERROR: SEND_ERROR"`
- 服务端发送消息：
  - 服务端发送：`"MESSAGE#[senderID]#[userID/groupID]#[message]"`
  - 客户端返回:  `"RECEIVE_OK"` / `"ERROR: RECEIVE_ERROR"`
- 请求好友/群聊信息：
  - 客户端发送：
    * `"SIGNUP_USER_INFO_REQUEST#[userID]"` // = FRIEND_INFO_REQUEST
    * `"GROUP_INFO_REQUEST#[groupID]"`
  - 服务端返回：
    * `"FRIEND_INFO#[userInfo.toString]"` / `"ERROR: FRIEND_INFO_ERROR"`
    * `"GROUP_INFO#[groupInfo.toString()]"`
- 请求好友/群聊历史消息：
  - 客户端发送：
    - `"FRIEND_HISTORY_REQUEST#[userID]#[friendID]"`
    - `"GROUP_HISTORY_REQUEST#[groupID]"`
  - 服务端发送：
    - `"FRIEND_HISTORY#[userID]#[friendID]#[Message.toString()]" * n` / `"ERROR: FRIEND_HISTORY_ERROR"` // 好友已经单方删除，无法发送消息
    - `"GROUP_HISTORY#[groupID]#[Message.toString()]" * n`
- 

### 主页面

* 客户端请求好友/群聊列表：

  * 客户端发送：

    * `"FRIENDS_INFO_REQUEST#[userID]"`
    * `"GROUPS_INFO_REQUEST#[userID]"`

  * 服务端返回：

    * `"FRIENDS_INFO#[friendID]" * n`

    * `"GROUPS_INFO#[groupID]" * n`

* 客户端请求添加好友：

  * 客户端发送：
    * `"FRIEND_ADD_REQUEST#[userID]#[friendID]"`
  * 服务端返回：
    * `"FRIEND_ADD_OK"` /  `"ERROR: FRIEND_ADD_ERROR"`

* 客户端请求删除好友：

  * 客户端发送：
    * `"FRIEND_REMOVE_REQUEST#[userID]#[friendID]"`
  * 服务端返回：
    * `"FRIEND_REMOVE_OK"` /  `"ERROR: FRIEND_REMOVE_ERROR"`

* 客户端请求新建群聊：

  * 客户端发送：
    * `"GROUP_ADD_REQUEST#[groupInfo.toString()]"`
  * 服务端返回：
    * `"GROUP_ADD_OK"` / `"ERROR: GROUP_ADD_ERROR"` // 申请的群聊ID与用户ID冲突

* 客户端请求退出群聊：

  * 客户端发送：
    * `"GROUPUSER_REMOVE_REQUEST#[groupID]#[userID]"`
  * 服务端返回：
    * `"GROUPUSER_REMOVE_OK"` / `"ERROR: GROUPUSER_REMOVE_ERROR"`

个人信息页面：

* 个人信息修改请求：
  * 客户端发送：
    * `"USER_INFO_UPDATE_REQUEST#[userInfo.toString()]"`
  * 服务端返回：
    * `"USER_INFO_UPDATE_OK"` / `"ERROR: USER_INFO_UPDATE_ERROR"`



## 类表：
    注：详情已上传为.h与.cpp文件
```C++
class PublicInfo{
public:
    QString toString();
    PublicInfo(QString info="");
    PublicInfo(int      _headimgID,
               int      _userID,
               QString  _nickname,
               bool     _sex=0,
               QString  _label="")；
protected:
    int         headimgID;
    int         userID;
    QString     nickname;
    int         sex;
    QString     label;
};
class AllInfo:public PublicInfo{
public:
    QString toString();
    AllInfo(QString info="");
    AllInfo(   int      _headimgID,
               int      _userID,
               QString  _nickname,
               bool     _sex=0,
               QString  _passwordFindQuestion="",
               QString  _passwordFindAnswer="",
               QString  _password="",
               QString  _label="")；
private:
    QString passwordFindQuestion;
    QString passwordFindAnswer;
    QString password;
};


class Message{
public:
    QString toString() const;
    bool valid() const;
    Message();
    Message(QString info);
    Message(QString _messageData,int _senderID,int _receiverID);
private:
    int senderID;
    int receiverID;
    QDateTime datetime;
    QString messageData;
};

```



# 服务端接口

*   TcpServer类

    *   readAll()返回QByteArray
    *   转QString （还未处理中文）
    *   以QByteArray传出

*   信息处理

    *   void sig_modifyMsg(QString, QTcpSocket*); 	//接收用户的消息后激活该信号

    

# 编码：

*在软件编码阶段，开发者根据《软件系统详细设计报告》中对数据结构、算法分析和模块实现等方面的设计要求，开始具体的编写程序工作，分别实现各模块的功能，从而实现对目标系统的功能、性能、接口、界面等方面的要求。在规范化的研发流程中，编码工作在整个项目流程里最多不会超过1/2，通常在1/3的时间，所谓磨刀不误砍柴功，设计过程完成的好，编码效率就会极大提高，编码时不同模块之间的进度协调和协作是最需要小心的，也许一个小模块的问题就可能影响了整体进度，让很多程序员因此被迫停下工作等待，这种问题在很多研发过程中都出现过。编码时的相互沟通和应急的解决手段都是相当重要的，对于程序员而言，bug永远存在，你必须永远面对这个问题！*





# 测试：

*测试编写好的系统。交给用户使用，用户使用后一个一个的确认每个功能。软件测试有很多种：按照测试执行方，可以分为内部测试和外部测试；按照测试范围，可以分为模块测试和整体联调；按照测试条件，可以分为正常操作情况测试和异常情况测试；按照测试的输入范围，可以分为全覆盖测试和抽样测试。以上都很好理解，不再解释。总之，测试同样是项目研发中一个相当重要的步骤，对于一个大型软件，3个月到1年的外部测试都是正常的，因为永远都会有不可预料的问题存在。完成测试后，完成验收并完成最后的一些帮助文档，整体项目才算告一段落，当然日后少不了升级，修补等等工作，只要不是想通过一锤子买卖骗钱，就要不停的跟踪软件的运营状况并持续修补升级，直到这个软件被彻底淘汰为止。*





# 维护： 

