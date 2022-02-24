# QT学习笔记

> OS课设需要用到QT，之前学C艹的时候由于对这门课程的厌恶以及自己的懒惰没有好好学，也没有自己实践写当时的实验五，现在从头开始学一学。   
>
> 根据[QT Creator教程](http://c.biancheng.net/view/3886.html)学习QT，并产生了本篇笔记

在VMware15.5中模拟Ubuntu20.04环境，Linux环境下下载、安装QT，过程较繁琐，不一一赘述了。

## Tips：

QT下载：https://download.qt.io/archive/qt/5.14/5.14.2/可以直接下载,也可点击Detail选择镜像下载,会快很多.

下载完毕后应该是无法直接点开的,需要在命令行中输入下列代码获取权限.

```java
chmod +x qt-opensource-linux-x64-5.14.2.run
```

[QT Creator安装教程](http://c.biancheng.net/view/3886.html)

[修改中文界面](https://blog.csdn.net/lyc_daniel/article/details/11813657)

如果遇到了写好项目出现

```java
cannot find -IGL
collect2:error.ld returned 1 exit status
```

执行

```java
sudo apt-get install libgl1-mesa-dev
```

遇到

```java
E: Could not get lock /var/lib/dpkg/lock-frontend - open (11: Resource temporarily unavailable)
E: Unable to acquire the dpkg frontend lock (/var/lib/dpkg/lock-frontend), is another process using it?
```

执行

```java
sudo rm /var/lib/dpkg/lock-frontend
sudo rm /var/lib/dpkg/lock
sudo rm /var/cache/apt/archives/lock
```

再执行`apt-get`就可以了.

## QT编程涉及到的一些术语、名词

1. Project

   项目

2. MakeFile

   生成脚本，生成器make可以根据规范的Makefile自动生成目标程序，即，使得程序员只需关注代码本身而无需处理哪些代码文件更新了需要重新编译等等这些脏活累活。

3. Debug or Release ? 

   Debug即调试，Release即发行。

   Debug用于纠错，测试等，所以debug版本的程序臃肿、详细。 Release用于发布程序用于实际用途，会对二进制程序进行大量优化。

   Debug 版本和 Release 版本使用的库文件不一样：

   - Debug 版本程序通常链接的也是 Debug 版本的库文件，比如 libQt5Guid.a/Qt5Guid.dll，库文件的简短名（不含扩展名）都是以 d 结尾的，Debug 库通常都比较大 。
   - Release 版本程序链接的通常就是 Release 版本的库文件，Release 版本库文件名字比 Debug 版本库文件少一个字母 d ，如 libQt5Gui.a/Qt5Gui.dll，而且 Release 版本库一般都比 Debug 版本小很多，运行效率也高很多。

4. C++ 11

   C++版本标准

5. Dynamic Link  & Static Link

   Dynamic Link 即动态链接，Static Link 即静态链接。

   **动态链接库**

   目标程序通常不是独立的，需要调用别的库，所以编译生成程序的时候需要链接别的库，如果多个程序同时运行，每个程序都链接了同一个库，那么内存中就可能存在同一个库的很多很多副本，效益非常的低，所以引入了动态链接库，在内存中只存放一个副本，需要的就链接过来。

   使用动态库，也意味着程序需要链接到如 *.dll 或 *.so 文件，得提前装好动态库文件，然后目标程序才能正常运行。

   **静态链接库**

   静态库就是将链接库的代码和自己编写的代码都编译链接到一块，链接到静态库的程序通常比较大，但好处是运行时依赖的库文件很少，因为目标程序自己内部集成了很多库代码。

6. Explicit Linking & Implicit Linking

   Explicit Linking 即显式链接，Implicit Linking 即隐式链接，这两种都是动态链接库的使用方式。

   实话实说没太看懂...

## 分析第一个QT程序

通过[第一个Qt程序](http://c.biancheng.net/view/1817.html)实现了一个简单的窗口，里面打印了一个Label（通过.ui文件拖拽组件实现）

那么可不可以通过代码而非拖拽组件这样的形式完成窗口捏？答案当然是可以。

### 分析文件

我们知道，一个项目中主要包括了这样几个文件

* xxx.pro   //项目文件
* mainwindow.h   //头文件
* main.cpp          //main文件
* mianwindow.cpp  //mainwindow代码文件

下面一 一讲解各个文件

1. main.cpp

   非常熟悉的主函数文件，主要包含应用程序的入口函数——main函数

   C/C++中的main函数有着固定格式，类似的，QT界面程序中的main函数也有固定的格式，如下：

   ```c++
   int main(int argc, char* argv[]){
       QApplication a(argc, argv);
       //填充代码
       return a.exec();
   }
   ```

   点击项目中的`main.cpp`查看代码如下：

   ```c++
   #include "mainwindow.h"
   #include <QApplication>
   int main(int argc, char *argv[])
   {
       QApplication a(argc, argv);
       MainWindow w;
       w.show();
       return a.exec();
   }
   ```

   其中，MainWindow是一个自定义的继承了QMainWindow主窗口类的主窗口类，所以w自然就是实例化的一个对象，表示主窗口类。

   一般情况下，组件都是隐藏的，可以通过调用MainWindow类中的show()方法使其显示出来。

2. mainwindow.h & mainwindow.cpp

   代码如下

   ```c++
   //mainwindow.h
   #ifndef MAINWINDOW_H
   #define MAINWINDOW_H
   #include <QMainWindow>
   class MainWindow : public QMainWindow
   {
       Q_OBJECT
   public:
       MainWindow(QWidget *parent = 0);
       ~MainWindow();
   };
   #endif // MAINWINDOW_H
   
   //mainwindow.cpp
   #include "mainwindow.h"
   MainWindow::MainWindow(QWidget *parent)
       : QMainWindow(parent)
   {
   }
   MainWindow::~MainWindow()
   {
   }
   ```

   初始状态下，MainWindow 类由 Q_OBJECT、构造函数和析构函数组成，这里重点介绍一下

   * **Q_OBJECT**

     本质是一个已定义好的宏，所有需要“信号和槽”功能的组件都必须将 Q_OBJECT 作为 private 属性成员引入到类中。本节设计的界面程序不会用到“信号和槽”，因此可以删除 Q_OBJECT。

   * **带参的构造函数**

     `QWidget` 是所有组件的基类，借助 parent 指针，可以为当前窗口指定父窗口。例如窗口 中，`QLabel` 文本框位于主窗口中，主窗口就是它的父窗口。当父窗口被删除时，所有子窗口也会随之一起删除。当然也可以不指定父窗口，那么当前窗口就会作为一个独立的窗口，不会受到其它窗口的影响。

   此时若直接运行程序则会出现一个空的窗口

### 编码实现简易的窗口界面

尝试向主窗口添加一个之前那样的Label，修改MainWindow类(`MainWindow.h`)，向其中添加一个private的`QLabel`指针`lab`, 在`MainWindow.cpp`中通过调用它的带参构造函数创建一个`QLabel`对象赋给`lab`

*由此，我们就成功设计了一个包含文本框的窗口，这也是我们编写的第一个 Qt 程序。*撒:cherry_blossom::cherry_blossom::cherry_blossom::cherry_blossom:

## QT控件  & 事件

**Qt 控件**

又称组件或者部件，指用户看到的所有可视化界面以及界面中的各个元素，比如按钮、文本框、输入框等。

在xxx.ui文件中我们看到过在`Widget Box`栏中有很多现成的控件，其实，每个控件都由特定类表示，每个控件类都包含一些常用属性、方法等，且所有的控件类都直接或间接继承自QWidget类，实际开发中我们也可以通过继承的方法定义一个具有多个控件特性的新控件。

Qt 中所有可视化的元素都称为控件，我们习惯将带有标题栏、关闭按钮的控件称为窗口。教程中展示了两种常用的窗口，实现它们的类分别是 QMainWindow 和 QDialog。 

- QMainWindow 类生成的窗口自带菜单栏、工具栏和状态栏，中央区域还可以添加多个控件，常用来作为应用程序的主窗口；
- QDialog 类生成的窗口非常简单，没有菜单栏、工具栏和状态栏，但可以添加多个控件，常用来制作对话框。

窗口很少单独使用，它的内部往往会包含很多控件。当窗口弹出时，窗口包含的所有控件会一同出现；当窗口关闭时，窗口上的所有控件也会随之消失。

**Qt 事件**

Qt 事件指的是应用程序和用户之间的交互过程，例如用户按下某个按钮，点击某个输入框等等。实际上除了用户会与应用程序进行交互外，操作系统也会与应用程序进行交互，例如当某个定时任务触发时，操作系统会关闭应用程序，这也是一个事件。

前文提到过exec()函数，一个 Qt 界面程序要想接收事件，main() 函数中就必须调用 exec() 函数，它的功能就是使程序能够持续不断地接收各种事件。

Qt 程序可以接收的事件种类有很多，例如鼠标点击事件、鼠标滚轮事件、键盘输入事件、定时事件等。每接收一个事件，Qt 会分派给相应的**事件处理函数**来处理。所谓事件处理函数，本质就是一个普通的类成员函数，以用户按下某个 QPushButton 按钮为例，Qt 会分派给 QPushButton 类中的 mousePressEvent() 函数处理。

## ==信号和槽==

信号和槽是 Qt 特有的消息传输机制，它能将相互独立的控件关联起来。

在 Qt 中，用户和控件的每次**交互过程**称为一个**事件**

> 比如“用户点击按钮”是一个事件，“用户关闭窗口”也是一个事件。每个事件都会发出一个信号，例如用户点击按钮会发出“按钮被点击”的信号，用户关闭窗口会发出“窗口被关闭”的信号。

Qt中所有控件都配备有接收不同信号的能力（即有相关的时间处理函数），在接收到信号后做出相应的响应动作。

> 例如，按钮所在的窗口接收到“按钮被点击”的信号后，会做出“关闭自己”的响应动作；再比如输入框自己接收到“输入框被点击”的信号后，会做出“显示闪烁的光标，等待用户输入数据”的响应动作。

在Qt中，对信号做出的响应动作称为**槽**

信号和槽机制底层是通过函数间的相互调用实现的。每个信号都可以用函数来表示，称为**信号函数**；每个槽也可以用函数表示，称为**槽函数**。

> 例如，“按钮被按下”这个信号可以用 `clicked()` 函数表示，“窗口关闭”这个槽可以用 close() 函数表示，信号和槽机制实现“点击按钮会关闭窗口”的功能，其实就是 clicked() 函数调用 close() 函数的效果。

信号函数和槽函数通常位于某个类中，和普通的成员函数相比，它们的特别之处在于：

- 信号函数用 `signals` 关键字修饰，槽函数用 `public slots`、`protected slots` 或者 `private slots` 修饰。`signals` 和 `slots` 是 Qt 在 C++ 的基础上扩展的关键字，专门用来指明信号函数和槽函数；
- 信号函数只需要声明，不需要定义（实现），而槽函数需要定义（实现）。

### connect()函数实现信号和槽

connect() 是 `QObject` 类中的一个静态成员函数，专门用来关联指定的信号函数和槽函数。

关联某个信号函数和槽函数，需要搞清楚以下 4 个问题：

1. 信号发送者是谁？
2. 哪个是信号函数？
3. 信号的接收者是谁？
4. 哪个是接收信号的槽函数？

若要实现 "按下按钮后窗口关闭功能", 代码如下:

```c++
QWidget widget;
//定义一个按钮，它位于 widget 窗口中
QPushButton But("按钮控件",&widget);
```

这里创建了一个窗口和一个按钮,  信号发送者是 But 按钮对象，要发送的信号是“按钮被点击”，可以用 `QPushButton` 类提供的 `clicked()` 信号函数表示；信号的接收者是 widget 主窗口对象，“窗口关闭”作为信号对应的槽，可以用 `QWidget` 类提供的 `close()` 函数表示。

connect() 常见语法格式Ⅰ

```c++
QObject::connect(const QObject *sender, const char *signal, const QObject *receiver, const char *method, Qt::ConnectionType type = Qt::AutoConnection)
/*************************************************************
 * @param sender 信号的发送者
 * @param signal 信号函数，需要用signal()函数宏括起来
 * @param receiver 信号接收者
 * @param method 槽函数，需要用slot()宏括起来
 * @param type 用于指定关联方式，默认为`Qt::AutoConnection`
 ***************************************************************/
```

> 例如，使用connect()函数将But按钮的clicked()信号函数和widget窗口的close()槽函数关联起来, 代码如下:

```c++
connect(&But, SIGNAL(clicked()), &widget, SLOT(close()));
```

格式Ⅱ

```c++
QObject::connect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method, Qt::ConnectionType type = Qt::AutoConnection)
```

与格式Ⅰ相比,改进了指定信号函数和槽函数的方式,无需使用SIGNAL() 和 SLOT()了.

新版的关联代码如下:

```c++
connect(&But, &QPushButton::clicked, &widget, &QWidget::close);
```

一个 connect() 函数只能关联一个信号函数和一个槽函数，程序中可以包含多个 connect() 函数，能实现以下几种效果：

- 关联多个信号函数和多个槽函数；
- 一个信号函数可以关联多个槽函数，当信号发出时，与之关联的槽函数会一个接一个地执行，但它们执行的顺序是随机的，无法人为指定哪个先执行、哪个后执行；
- 多个信号函数可以关联同一个槽函数，无论哪个信号发出，槽函数都会执行。

### 实战信号和槽机制

暂无:sweat_smile:



## Qt QLabel文本框用法

`QLabel` 是 Qt 帮我们写好的一个控件类，间接继承自 `QWidget` 类，它的继承关系如下：

QLabel -> QFrame -> QWidget

### QLabel文本框的构造函数

QLabel提供了两个构造函数,分别是:

```c++
QLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
/*************************************************************
 * @param parent 用于指定文本框的父窗口
 * @param f 用于设置文本框的一些系统属性和外观属性,默认值为 Qt::Widget，表示当不指定父窗口             时，文本框将作为一个独立窗口
 * @exclamation `WindowFlags` 是一种枚举类型
 ***************************************************************/


QLabel(const QString &text, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags())
    
/*************************************************************
 * @param text 用于指定文本框中显示的文字
 ***************************************************************/
```

### QLabel类常用属性&方法

| 属 性           | 含 义                                                        |
| --------------- | ------------------------------------------------------------ |
| alignment       | 保存 QLabel 控件中内容的对齐方式，默认情况下，QLabel 控件中的内容保持左对齐和垂直居中。  该属性的值可以通过调用 alignment() 方法获得，可以借助 setAlignment() 方法修改。 |
| text            | 保存 QLabel 控件中的文本，如果 QLabel 控件中没有文本，则 text 的值为空字符串，  该属性的值可以通过 text() 方法获得，可以借助 setText() 方法修改。 |
| pixmap          | 保存 QLabel 控件内显示的图片，如果控件内没有设置图片，pixmap 的值为 0。  该属性的值可以通过调用 pixmap() 方法获得，可以借助 setPixmap() 方法修改。 |
| selectedText    | 保存 QLabel 控件中被选择了的文本，当没有文本被选择时，selectedText 的值为空字符串。  该属性的值可以通过调用 selectedText() 方法获得。 |
| hasSelectedText | 判断用户是否选择了 QLabel 控件内的部分文本，如果是则返回 true，反之则返回 false。默认情况下，该属性的值为 false。 |
| indent          | 保存 QLabel 控件内文本的缩进量，文本的缩进方向和 alignment 属性的值有关。  该属性的值可以通过调用 indent() 方法获得，可以借助 setIndent() 方法修改。 |
| margin          | 保存 QLabel 控件中内容与边框之间的距离（边距），margin 的默认值为 0。  该属性的值可以通过调用 margin() 方法获得，可以借助 setMargin() 方法修改。 |
| wordWrap        | 保存 QLabel 控件内文本的换行策略。当该属性的值为 true 时，控件内的文本会在必要时自动换行。默认情况下，控件内的文本是禁止自动换行的。  该属性的值可以通过 wordWrap() 方法获得，可以借助 setWordWrap() 方法修改。 |

| 成员方法                                | 功 能                                                        |
| --------------------------------------- | ------------------------------------------------------------ |
| hide()                                  | 隐藏文本框。                                                 |
| clear()                                 | 清空 QLabel 控件内所有显示的内容。                           |
| setToolTip(QString)                     | 设置信息提示，当用户的鼠标放在QLabel 文本框上时会自动跳出文字。 |
| setToolTipDuration(int)                 | 设置提示信息出现的时间，单位是毫秒。                         |
| setStyleSheet(QString)                  | 设置 QLabel 文本框的样式。                                   |
| setGeometry(int x, int y, int w, int h) | 设置 QLabel 文本框的位置 (x, y) 以及尺寸 (w, h)。            |

### QLabel文本框的信号和槽

QLabel 控件只用来显示文本、图像等内容，很好与用户交互。但是，当 QLabel 控件内包含超链接内容时，可以使用 QLabel 类提供的两个信号函数：

| 信号函数                           | 功 能                                                        |
| ---------------------------------- | ------------------------------------------------------------ |
| linkActivated(const QString &link) | 用户点击超链接时触发，link 参数用于向槽函数传输超链接的 URL。 |
| linkHovered(const QString &link)   | 用户的鼠标悬停到超链接位置时触发，link 参数用于向槽函数传输超链接的 URL。 |

| 槽函数                              | 功 能                                                        |
| ----------------------------------- | ------------------------------------------------------------ |
| clear()                             | 清空 QLabel 控件内所有的内容。                               |
| setMovie(QMovie *movie)             | 清空 QLabel 控件内所有的内容，改为显示指定的 movie 动画。    |
| setNum(int num)                     | 清空 QLabel 控件内所有的内容，改为显示 num 整数的值。        |
| setNum(double num)                  | 清空 QLabel 控件内所有的内容，改为显示 num 小数的值。        |
| setPicture(const QPicture &picture) | 清空 QLabel 控件内所有的内容，改为显示经 QPicture 类处理的图像。 |
| setPixmap(const QPixmap &)          | 清空 QLabel 控件内所有的内容，改为显示经 QPixmap 类处理的图像。 |
| setText(const QString &)            | 清空 QLabel 控件内所有的内容，改为显示指定的文本。           |

## QPushButton按钮用法

Qt 提供了很多种按钮，比如 QPushButton（普通按钮）、QRadioButton（单选按钮）、QToolButton（工具栏按钮）等。QPushButton 是实际开发中最常使用的一种按钮，

### QPushButton按钮的创建

继承关系: QPushButton -> QAbstractButton -> QWidget

### QPushButton按钮的构造函数

```c++
QPushButton(QWidget *parent = Q_NULLPTR)
QPushButton(const QString &text, QWidget *parent = Q_NULLPTR)
QPushButton(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR)
/*************************************************************
 * @param parent 用于指定文本框的父窗口
 * @param text 用于指定文本框中显示的文字
 * @param icon 用于设置按钮上要显示的图标
 ***************************************************************/
```

### QPushButton按钮常用属性&方法

| 属 性       | 含 义                                                        |
| ----------- | ------------------------------------------------------------ |
| text        | 保存按钮上要显示的文字。  该属性的值可以通过 text() 方法获取，也可以通过 setText(const QString &text) 方法修改。 |
| icon        | 保存按钮左侧要显示的图标。  该属性的值可以通过 icon() 方法获取，也可以通过 setIcon(const QIcon &icon) 方法修改。 |
| iconsize    | 保存按钮左侧图标的尺寸。  该属性的值可以通过 iconSize() 方法获取，也可以通过 setIconSize(const QSize &size) 方法修改。 |
| size        | 保存按钮的尺寸。  该属性的值可以通过 size() 方法获取，也可以通过 resize(int w, int h) 或者 resize(const QSize &) 方法修改。 |
| font        | 保存按钮上文字的字体和大小。  该属性的值可以通过 font() 方法获取，也可以通过 setFont(const QFont &) 方法修改。 |
| flat        | 初始状态下，按钮是否显示边框。flat 属性的默认值为 flase，表示按钮带有边框。  该属性的值可以通过 isFlat() 方法获取，也可以通过 setFlat(bool) 方法修改。 |
| enabled     | 指定按钮是否可以被按下。  该属性的默认值为 true，表示按钮可以被按下，即按钮处于启用状态。当该属性的值为 false 时，按钮将不能被点击，按钮处于禁用状态。  该属性的值可以通过 isEnabled() 方法获取，也可以通过 setEnabled(bool) 方法进行修改。 |
| autoDefault | 当用户按下 Enter 回车键时，是否触发点击按钮的事件。  当按钮的父窗口为 QDialog 窗口时，该属性的值为 true；其它情况下，该属性的默认值为 false。  该属性的值可以通过 autoFault() 方法获取，也可以通过 setAutoFault(bool) 方法修改。 |

| 方 法                                    | 功 能                                                        |
| ---------------------------------------- | ------------------------------------------------------------ |
| move(int x, int y)                       | 手动指定按钮位于父窗口中的位置。                             |
| setStyleSheet(const QString &styleSheet) | 自定义按钮的样式，包括按钮上文字或图片的显示效果，按钮的形状等等。 |
| setGeometry(int x, int y, int w, int h)  | 同时指定按钮的尺寸和位置。                                   |
| adjustSize()                             | 根据按钮上要显示的内容，自动调整按钮的大小。                 |
| setDisabled(bool disable)                | 指定按钮是否可以被按下。当 disable 值为 true 时，表示按钮不能被按下，即禁用按钮的功能。 |

### QPushButton按钮信号和槽

| 信号函数                                | 功 能                                                        |
| --------------------------------------- | ------------------------------------------------------------ |
| clicked() clicked(bool checked = false) | 用户点击按钮并释放（或者按下按钮对应的快捷键）后，触发此信号。 |
| pressed()                               | 用户按下按钮时会触发此信号。                                 |
| released()                              | 用户松开按钮时会触发此信号。                                 |
| 槽函数                                  | 功 能                                                        |
| click()                                 | 单击指定的按钮。                                             |
| setIconSize()                           | 重新设置按钮上图片的尺寸。                                   |
| hide()                                  | 隐藏按钮控件。                                               |
| setMenu(QMenu *menu)                    | 弹出与按钮关联的菜单。                                       |

