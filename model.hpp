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
class custom_button : QPushButton {
    Q_OBJECT
public:
    explicit custom_button(QWidget* parent = nullptr);
};
struct part {
    int width;
    int height;
    int startx;
    int starty;
    int hue;
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

private:


    std::vector<part> parts{ 
        {192,396,72,334,0},                 //legs
        {90,112,123,0,0},                   //head
        {124,222,108,112,0},                //torso
        {53,76,0,335,0},                    //hands_R
        {53,76,291,335,0},                  //hands_L
        {108,223,0,112,0},                  //arms_R
        {108,223,232,112,0},                //arms_L
        {48,36,161,198,0},                  //stomach
        {37,47,153,154,0},                  //heart
        //{342,730,0,0,0}                     //skeleton
    };


    void updateallcols();
    void resetcols();



    custom_label* body_label;
    custom_button* submit;
    custom_button* reset;

    custom_field* total_assets;
    custom_field* total_revenue;
    custom_field* total_marketing_cost;
    custom_field* total_salaries;
    custom_field* cogs_perc;
    custom_field* cogs_value;
    custom_field* total_expenses;



    Ui::filecryptClass ui;


    int heart_hue{ 0 };
    int brain_hue{ 0 };
    int heart_size{ 60 };
    int brain_size{ 60 };

};
