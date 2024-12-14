#pragma once

#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <qfile.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qpropertyanimation.h>
#include <qaction.h>
#include <qregularexpression.h>
#include <qstyle.h>
#include <qwidget.h>
#include <qsvgrenderer.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qcolor.h>
#include <qstyleoption.h>
#include <QGraphicsDropShadowEffect>
#include <QSequentialAnimationGroup>
#include <qproperty.h>
#include <qslider.h>
#include <qlineedit.h>
#include <qdial.h>
#include <qevent.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qrect.h>

#include <iostream>

//#include <qmap.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qtextedit.h>

#include <vector>


#include "ui_model.h"


namespace stylesheets {
    inline QString base_field{ "QLineEdit{\
                            border:0.5px solid silver;\
                            border-radius:8px;\
                            padding:17px 20px 17px 20px;\
                            margin:0px 0px 0px 0px;\
                            color:black;\
                         }" };
    inline QString error_field{ "QLineEdit{\
                            border:0.5px solid red;\
                            border-radius:8px;\
                            padding:17px 20px 17px 20px;\
                            margin:0px 0px 0px 0px;\
                            color:black;\
                         }" };
    inline QString warning_field{ "QLineEdit{\
                            border:0.5px solid orange;\
                            border-radius:8px;\
                            padding:17px 20px 17px 20px;\
                            margin:0px 0px 0px 0px;\
                            color:black;\
                         }" };
    inline QString success_field{ "QLineEdit{\
                                border:0.5px solid green;\
                                border-radius:8px;\
                                padding:17px 20px 17px 20px;\
                                margin:0px 0px 0px 0px;\
                                color:black;\
                             }" };
    inline QString disabled_field{ "QLineEdit{\
                                border:0.5px solid lightgray;\
                                border-radius:8px;\
                                padding:17px 20px 17px 20px;\
                                margin:0px 0px 0px 0px;\
                                color:lightgray;\
                             }" };
    inline QString base_label{ "margin:42px 12px 16px 12px;\
                                color:black;\
                                padding:0px 2px 0px 2px;\
                                background-color:transparent;\
                                border-radius:4px" };
    inline QString error_label{ "margin:42px 12px 16px 12px;\
                                color:red;\
                                padding:0px 2px 0px 2px;\
                                background-color:transparent;\
                                border-radius:4px" };
    inline QString warning_label{ "margin:42px 12px 16px 12px;\
                                color:orange;\
                                padding:0px 2px 0px 2px;\
                                background-color:transparent;\
                                border-radius:4px" };
    inline QString success_label{ "margin:42px 12px 16px 12px;\
                                color:green;\
                                padding:0px 2px 0px 2px;\
                                background-color:transparent;\
                                border-radius:4px" };
    inline QString disabled_label{ "margin:42px 12px 16px 12px;\
                                color:lightgray;\
                                padding:0px 2px 0px 2px;\
                                background-color:transparent;\
                                border-radius:4px" };
}


class custom_field : public QLineEdit {
    Q_OBJECT
        Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
        Q_PROPERTY(float borderRadius READ borderRadius WRITE setBorderRadius)
public:
    QColor borderColor() const { return m_borderColor; }
    void setBorderColor(const QColor& color) {
        m_borderColor = color;
        update();  // Trigger a repaint
    }

    float borderRadius() const { return m_borderRadius; }
    void setBorderRadius(float radius) {
        this->setStyleSheet(QString("QLineEdit{\
                                border:%1px solid %2;\
                                border-radius:8px;\
                                padding:17px 20px 17px 20px;\
                                margin:0px 0px 0px 0px;\
                             }").arg(radius).arg(m_borderColor.name()));
        update();  // Trigger a repaint
    }
    explicit custom_field(QString placeholdertext,bool secret = false ,QWidget* parent = nullptr);
    QString current_password{};
    bool valid_pass{ false };
    QLabel* placeholder_background{ nullptr };
    QLabel* placeholder_text{ nullptr };
    std::optional<QPushButton*> eye;
    std::optional<QPropertyAnimation*> shake_anim;
    QPropertyAnimation* rise_anim;
    QPropertyAnimation* fall_anim;
    QPropertyAnimation* rise_anim_back;
    QPropertyAnimation* fall_anim_back;
    std::vector<QPropertyAnimation*> focus_anim;
    template<typename T>
    static std::vector<QPropertyAnimation*> focus(T* anim);
    template<typename T>
    static QPropertyAnimation* coloranim(T* anim, const QColor& col, const QColor& col_to);
    QColor p_borderColor{QColor("silver")};
protected:
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
private:
    QGraphicsDropShadowEffect* shadow;
    bool secret{ false };
    template<typename T>
    static QPropertyAnimation* shake(T* anim);
    template<typename T>
    static QPropertyAnimation* rise(T* anim);
    template<typename T>
    static QPropertyAnimation* fall(T* anim);
    QAction* eye_action;
    QColor m_borderColor;
    int m_borderRadius;
};
class custom_label : QLabel {
    Q_OBJECT
public:
    explicit custom_label(QImage img, QWidget* parent = nullptr);
    bool eventFilter(QObject* obj, QEvent* ev);
    QImage bodyimg;
    QImage orig;
    void rerender();
    void reset();
protected:
    void enterEvent(QEnterEvent* event) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
private:
    //void hoverEvent(QLeaveEvent* ev) override;
    //void focusOutEvent(QFocusEvent* event) override;
    //void resizeEvent(QResizeEvent* event) override;

};
class custom_hoverbox : QLabel {
    Q_OBJECT
public:
    explicit custom_hoverbox(QString msg,QWidget* parent = nullptr);
    void visible2();
    void visiblefalse();
    //bool eventFilter(QObject* obj, QEvent* ev);
    //void rerender();
    //void reset();
protected:
    //void enterEvent(QEnterEvent* event) override;
    //void mouseMoveEvent(QMouseEvent* ev) override;
private:
    //void hoverEvent(QLeaveEvent* ev) override;
    //void focusOutEvent(QFocusEvent* event) override;
    //void resizeEvent(QResizeEvent* event) override;

};
class custom_button : QPushButton {
    Q_OBJECT
public:
    explicit custom_button(QString placeholder,QWidget* parent = nullptr);
protected:
    void resizeEvent(QResizeEvent* event) override;
};
struct part {
    QRect dim;
    std::function<double()> huefn;
    std::function<int(double)> hue;
    std::function<void()> disp = [] { qInfo() << QString("hello");};
    std::function<void()> hide = [&] { qInfo() << QString("goodbye");};
};


class model : public QMainWindow
{
    Q_OBJECT

public:
    model(QWidget* parent = nullptr);



    void updateheartcol(int value);
    void updatebraincol(int value);
    void updateheartsize(int value);
    void updatebrainsize(int value);


    ~model();

    void changeSvg(const QString& svgPath, const QColor& newColor, QLabel* label,int size);


    static inline custom_field* total_assets;
    static inline custom_field* total_revenue;
    static inline custom_field* total_marketing_cost;
    static inline custom_field* total_salaries;
    static inline custom_field* cogs_perc;
    static inline custom_field* cogs_value;
    static inline custom_field* total_expenses;

    static inline custom_field* employees_left;
    static inline custom_field* average_total_employees;
    static inline custom_field* total_units;
    static inline custom_field* production_hour;
    static inline custom_field* material_cost;
    static inline custom_field* marketing_cost;
    static inline custom_field* new_products;
    static inline custom_field* total_products;
    static inline custom_field* current_revenue;
    static inline custom_field* previous_revenue;

    static inline const std::function<double()> head = [] { if (total_revenue->text().isEmpty() || cogs_value->text().isEmpty()) return 0.0; else return (total_revenue->text().toDouble() - cogs_value->text().toDouble()) / total_revenue->text().toDouble() * 100.0;};
    static inline const std::function<double()> heart = [] { if (employees_left->text().isEmpty() || average_total_employees->text().isEmpty()) return 100.0; else return (employees_left->text().toDouble() / average_total_employees->text().toDouble()) * 100.0;};
    static inline const std::function<double()> arms = [] { if (total_units->text().isEmpty() || production_hour->text().isEmpty()) return 0.0; else return (total_units->text().toDouble() / production_hour->text().toDouble());};
    static inline const std::function<double()> hands = [] { if (material_cost->text().isEmpty() || total_revenue->text().isEmpty()) return 100.0; else return (material_cost->text().toDouble() / total_revenue->text().toDouble()) * 100.0;};
    static inline const std::function<double()> stomach = [] { if (marketing_cost->text().isEmpty() || total_revenue->text().isEmpty()) return 100.0; else return (marketing_cost->text().toDouble() / total_revenue->text().toDouble()) * 100.0;};
    static inline const std::function<double()> torso = [] { if (new_products->text().isEmpty() || total_products->text().isEmpty()) return 0.0; else return (new_products->text().toDouble() / total_products->text().toDouble()) * 100.0;};
    static inline const std::function<double()> legs = [] { if (current_revenue->text().isEmpty() || previous_revenue->text().isEmpty()) return 0.0; else return ((current_revenue->text().toDouble() - previous_revenue->text().toDouble()) / previous_revenue->text().toDouble()) * 100.0;};

    static inline const std::function<int(double)> headmap = [](double perc) {
        return static_cast<int>(std::clamp(4.0 * perc - 40.0, 0.0, 120.0));

        };
    static inline const std::function<int(double)> heartmap = [](double perc) {
        return static_cast<int>(std::clamp((- 6.0 * perc + 165.0), 0.0, 120.0));

        };
    static inline const std::function<int(double)> armsmap = [](double perc) {
        return static_cast<int>(std::clamp(4.0 * perc - 260.0, 0.0, 120.0));

        };
    static inline const std::function<int(double)> handsmap = [](double perc) {
        return static_cast<int>(std::clamp(-4.0 * perc + 280.0, 0.0, 120.0));

        };
    static inline const std::function<int(double)> stomachmap = [](double perc) {
        return static_cast<int>(std::clamp(-12.0 * perc + 210.0, 0.0, 120.0));

        };
    static inline const std::function<int(double)> torsomap = [](double perc) {
        return static_cast<int>(std::clamp(12.0 * perc - 30.0, 0.0, 120.0));

        };
    static inline const std::function<int(double)> legsmap = [](double perc) {
        return static_cast<int>(std::clamp(20.0 * perc - 70.0, 0.0, 120.0));

        };
    //static inline const std::function<int(double)> headmap = [](double perc) { { qInfo() << static_cast<int>(std::clamp(perc, 0.0, 120.0)) << "  AAA  " << std::clamp(perc, 0.0, 120.0) << "  AAA  " << perc; return static_cast<int>(std::clamp(perc, 0.0, 120.0)); }};

    static inline  custom_hoverbox* head_hover = nullptr;
    static inline  custom_hoverbox* heart_hover = nullptr;
    static inline  custom_hoverbox* arms_hover = nullptr;
    static inline  custom_hoverbox* torso_hover = nullptr;
    static inline  custom_hoverbox* legs_hover = nullptr;
    static inline  custom_hoverbox* hands_hover = nullptr;
    static inline  custom_hoverbox* stomach_hover = nullptr;
    //static inline  custom_hoverbox* skeleton_hover = nullptr;




    static inline  custom_hoverbox* extra_fluff = nullptr;



    static inline const std::vector<part> parts{
        {{72,334,192,396},legs,legsmap,[] { legs_hover->visible2();},[] { legs_hover->visiblefalse();}},                 //legs
        {{123,0,90,112},head,headmap,[] { head_hover->visible2();},[] { head_hover->visiblefalse();}},                   //head
        {{108,112,124,222},torso,torsomap,[] { torso_hover->visible2();},[] { torso_hover->visiblefalse();}},                //torso
        {{0,335,53,76},hands,handsmap,[] { hands_hover->visible2();},[] { hands_hover->visiblefalse();}},                    //hands_R
        {{291,335,51,76},hands,handsmap,[] { hands_hover->visible2();},[] { hands_hover->visiblefalse();}},                  //hands_L
        {{0,112,108,223},arms,armsmap,[] { arms_hover->visible2();},[] { arms_hover->visiblefalse();} },                  //arms_R
    { {232,112,106,223},arms,armsmap,[] { arms_hover->visible2();},[] { arms_hover->visiblefalse();} },                //arms_L
        //{{342,730,0,0},[]{return static_cast<int>(total_assets->text().toDouble()/total_revenue->text().toDouble());}}                     //skeleton
    };
    //^^^^^^^^^^^^^^^^^^^^^^skeleton^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^2

    static inline const std::vector<part> parts2{
        {{153,154,37,45},heart,heartmap,[] { heart_hover->visible2();},[] { heart_hover->visiblefalse();}},                  //heart
        { { 161,200,48,36 },stomach,stomachmap,[] { stomach_hover->visible2();},[] { stomach_hover->visiblefalse();} },                  //stomach
    };

    void updateallcols();
    void resetcols();


   const QString msgstomach = "The stomach 'nourishes' the company by bringing in new customers, similar to how marketing acquires and sustains customer relationships.";
   const QString msghead = "The head is responsible for planning, strategic thinking, and managing risks, just as finance oversees financial stability and risk management.";
   const QString msgheart = "The heart represents employee morale and engagement, essential for keeping the company's 'lifeblood' (employees) flowing and engaged.";
   const QString msgarms = "The arms are associated with action and execution, symbolizing the ability to perform tasks efficiently in operations.";
   const QString msgtorso = "The torso represents the core, housing vital organs, like production and engineering, that keep the company functioning.";
   const QString msglegs = "The legs propel the company forward, representing sales, which drive revenue growth and keep the business moving.";
   const QString msghands = "The hands manage sourcing and material acquisition, symbolizing how procurement supplies the company with necessary resources.";


private:

    custom_label* body_label;
    custom_button* submit;
    custom_button* reset;


    Ui::filecryptClass ui;


    int brain_hue{ 0 };
    int heart_hue{ 0 };
    int skeleton_hue{ 0 };
    int arms_hue{ 0 };
    int hands_hue{ 0 };
    int stomach_hue{ 0 };
    int torso_hue{ 0 };
    int legs_hue{ 0 };

};
//class HoverRegionWidget : public QWidget
//{
//    Q_OBJECT
//
//public:
//    HoverRegionWidget(QWidget* parent = nullptr) : QWidget(parent)
//    {
//        setMouseTracking(true); // Enable mouse tracking
//        imageLabel = new QLabel(this);
//        imageLabel->setPixmap(QPixmap(":/path/to/your/image.png"));
//        imageLabel->setAlignment(Qt::AlignCenter);
//        imageLabel->setMouseTracking(true);
//
//        infoBox = new QWidget(this);
//        infoBox->setStyleSheet("background-color: rgba(0, 0, 0, 150); border: 2px solid white; padding: 10px;");
//        infoBox->setHidden(true);
//
//        infoText = new QTextEdit(infoBox);
//        infoText->setReadOnly(true);
//
//        QVBoxLayout* boxLayout = new QVBoxLayout(infoBox);
//        boxLayout->addWidget(infoText);
//
//        QVBoxLayout* mainLayout = new QVBoxLayout(this);
//        mainLayout->addWidget(imageLabel);
//        setLayout(mainLayout);
//
//        // Define regions and their corresponding content
//        regions = {
//            {{50, 50, 100, 100}, "Info for Region 1"},
//            {{200, 150, 150, 150}, "Info for Region 2"},
//            {{400, 300, 100, 200}, "Info for Region 3"}
//        };
//    }
//
//protected:
//    void mouseMoveEvent(QMouseEvent* event) override {
//        QPoint mousePos = event->pos();
//        bool found = false;
//
//        // Check if the mouse is in any defined region
//        for (const auto& region : regions.keys()) {
//            if (region.contains(mousePos)) {
//                infoText->setText(regions[region]);
//                infoBox->setGeometry(mousePos.x() + 15, mousePos.y() + 15, 200, 100); // Adjust position relative to mouse
//                infoBox->setVisible(true);
//                found = true;
//                break;
//            }
//        }
//
//        if (!found) {
//            infoBox->setVisible(false); // Hide the box if no region is matched
//        }
//    }
//
//private:
//    QLabel* imageLabel;
//    QWidget* infoBox;
//    QTextEdit* infoText;
//
//    // Map to store regions and their corresponding content
//    QMap<QRect, QString> regions;
//};
