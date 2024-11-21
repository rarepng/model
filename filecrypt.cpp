#include "filecrypt.hpp"

#include <iostream>
#include <qfile.h>





model::model(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);



    connect(ui.browse, &QAbstractButton::clicked, this, &model::browse);
    connect(ui.dial_heart, &QDial::valueChanged, this, &model::updateheartcol);
    connect(ui.dial_brain, &QDial::valueChanged, this, &model::updatebraincol);
    connect(ui.slider_heart, &QSlider::valueChanged, this, &model::updateheartsize);
    connect(ui.slider_brain, &QSlider::valueChanged, this, &model::updatebrainsize);
    //connect(ui.body,SIGNAL(clicked()))

    QImage body{ "body.png" };
    
    qInfo() << body.size();

    //for (size_t i{ 200 }; i < 400; i++) {
    //    for (size_t j{ 200 }; j < 400; j++) {
    //        QColor c = body.pixelColor(i, j);

    //        c.setHsv(0, c.saturation()+160, c.value(), c.alpha());
    //        body.setPixelColor(i, j, c);
    //    }
    //}

    body.convertToFormat(QImage::Format_RGBA8888);
    qInfo() << body.size();

    //ui.body->setPixmap(QPixmap::fromImage(body));


    namefield = new custom_field("field", false, ui.name_grid);

    body_label = new custom_label(body,ui.body);


    //defaultline = ui.line0->styleSheet();



    ui.browse->setIcon(QIcon{ "file.svg" });
    changeSvg("brain.svg", QColor::fromHsv(brain_hue,255,255), ui.brain,60);
    changeSvg("heart.svg", QColor::fromHsv(heart_hue, 255, 255), ui.heart,60);
    


}



void model::browse() {
    std::cout << "clicked";
}





void model::updateheartcol(int value) {
    heart_hue = value;
    changeSvg("heart.svg", QColor::fromHsv(value, 255, 255), ui.heart, heart_size);
}
void model::updatebraincol(int value) {
    brain_hue = value;
    changeSvg("brain.svg", QColor::fromHsv(value, 255, 255), ui.brain, brain_size);
}
void model::updateheartsize(int value) {
    heart_size = value;
    changeSvg("heart.svg", QColor::fromHsv(heart_hue, 255, 255), ui.heart, value);
}
void model::updatebrainsize(int value) {
    brain_size = value;
    changeSvg("brain.svg", QColor::fromHsv(brain_hue, 255, 255), ui.brain, value);
}

model::~model() {}



custom_field::custom_field(QString placeholdertext, bool secret, QWidget* parent) : QLineEdit(parent) {

    this->mapToParent(QPoint(0, 0));

    this->setGeometry(parent->rect());

    this->setStyleSheet(stylesheets::base_field);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->adjustSize();

    placeholder_background = new QLabel{ placeholdertext,parent };
    placeholder_background->mapToParent(QPoint(0, 0));
    placeholder_background->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    placeholder_background->setStyleSheet("margin:42px 12px 16px 12px;color:black;padding:0px 2px 0px 2px;color:transparent;background-color:white;border-radius:4px");
    placeholder_background->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    placeholder_background->adjustSize();

    placeholder_text = new QLabel{ placeholdertext,placeholder_background };
    placeholder_text->mapToParent(QPoint(0, 0));
    placeholder_text->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    placeholder_text->setStyleSheet("margin:42px 12px 16px 12px;color:black;padding:0px 2px 0px 2px;background-color:transparent;border-radius:4px");
    placeholder_text->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    focus_anim = focus(this);

    rise_anim = rise(placeholder_background);
    fall_anim = fall(placeholder_background);
    rise_anim_back = rise(placeholder_text);
    fall_anim_back = fall(placeholder_text);





    if (secret) {

        this->setEchoMode(QLineEdit::Password);

        this->secret = true;

        eye_action = new QAction{ QIcon{ "eye_open.svg" },"",this };
        this->addAction(eye_action, QLineEdit::TrailingPosition);

        connect(eye_action, &QAction::triggered, [=]() {
            this->setEchoMode(this->echoMode() == QLineEdit::Normal ? QLineEdit::Password : QLineEdit::Normal);
            eye_action->setIcon(this->echoMode() == QLineEdit::Normal ? QIcon{ "eye.svg" } : QIcon{ "eye_open.svg" });
            });

        connect(this, &QLineEdit::editingFinished, [&]() {
            if (!this->current_password.isEmpty() && !this->valid_pass) {
                this->addAction(eye_action, QLineEdit::TrailingPosition);
                shake_anim.reset();
                shake_anim = shake((QWidget*)this->parent());
            }
            });



        shake_anim = shake((QWidget*)this->parent());
    }

}
custom_label::custom_label(QImage img, QWidget* parent) : QLabel(parent) {

    this->installEventFilter(this);


    this->bodyimg = img;

    this->mapToParent(QPoint(0, 0));

    this->setGeometry(parent->rect());
    this->setPixmap(QPixmap::fromImage(img));

    //this->setStyleSheet(stylesheets::base_field);
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->adjustSize();
    this->setMouseTracking(true);
    //parent->setMouseTracking(true);

}

bool custom_label::eventFilter(QObject* obj, QEvent* ev){
    if (ev->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(ev);
        QImage newbody{};
        for (int i{ mouseEvent->pos().x() }; i < mouseEvent->pos().x() + 20; i++) {
            for (int j{ mouseEvent->pos().y() }; j < mouseEvent->pos().y() + 20; j++) {
                QColor c = this->bodyimg.pixelColor(i, j);

                c.setHsv(0, c.saturation(), c.value(), c.alpha());
                this->bodyimg.setPixelColor(i, j, c);
                //qInfo() << 
            }
        }
        this->setPixmap(QPixmap::fromImage(this->bodyimg));
        //qInfo() << mouseEvent->pos();
    }
    return false;
}

void custom_field::focusInEvent(QFocusEvent* event) {
    QLineEdit::focusInEvent(event);
    if (this->text().isEmpty()) {
        rise_anim->start(QAbstractAnimation::KeepWhenStopped);
        shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(4);
        shadow->setColor(QColor(0, 0, 0, 180));
        shadow->setOffset(-2, 2);
        this->placeholder_text->setGraphicsEffect(shadow);
        QPropertyAnimation* color_anim = coloranim<custom_field>(this, p_borderColor, QColor("black"));
        color_anim->start(QAbstractAnimation::DeleteWhenStopped);
        p_borderColor = QColor("black");
    }
    for (auto i : focus_anim)i->start(QAbstractAnimation::KeepWhenStopped);
    QSequentialAnimationGroup* anim_group = new QSequentialAnimationGroup();
    QPropertyAnimation* color_anim = coloranim<custom_field>(this, p_borderColor, QColor(255,165,0));
    QPropertyAnimation* color_anim_back = coloranim<custom_field>(this, QColor("orange"), p_borderColor);
    anim_group->addAnimation(color_anim);
    anim_group->addAnimation(color_anim_back);
    anim_group->start(QAbstractAnimation::DeleteWhenStopped);
}

void custom_field::focusOutEvent(QFocusEvent* event) {
    QLineEdit::focusOutEvent(event);

    if (this->text().isEmpty()) {
        fall_anim->start(QAbstractAnimation::KeepWhenStopped);
        this->placeholder_text->setGraphicsEffect(nullptr);
        this->setStyleSheet(stylesheets::base_field);
        //fall_anim.lock()->start();
    }else if(this->secret&&!valid_pass){
        shake_anim.value()->start(QAbstractAnimation::KeepWhenStopped);
    }
}

void custom_field::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);
    qInfo() << "resize";
    QRect tmp = ((QWidget*)this->parent())->rect();
    this->setGeometry(tmp.x(), tmp.y()+24, tmp.width(), tmp.height()-24);

    

    if (this->secret) {
        this->addAction(eye_action, QLineEdit::TrailingPosition);
        shake_anim.reset();
        shake_anim = shake((QWidget*)this->parent());
    }
}




template <typename T>
QPropertyAnimation* custom_field::shake(T* anim) {
    QPropertyAnimation* shake_anim = new QPropertyAnimation(anim, "pos");
    shake_anim->setDuration(250);
    shake_anim->setEasingCurve(QEasingCurve::InOutQuad);
    shake_anim->setKeyValueAt(0, anim->pos());
    shake_anim->setKeyValueAt(0.25, anim->pos() + QPoint(6, 0));
    shake_anim->setKeyValueAt(0.5, anim->pos() + QPoint(-6, 0));
    shake_anim->setKeyValueAt(0.75, anim->pos() + QPoint(6, 0));
    shake_anim->setKeyValueAt(1, anim->pos());
    return shake_anim;
}

template<typename T>
QPropertyAnimation* custom_field::rise(T* anim) {
    QPropertyAnimation* rise_anim = new QPropertyAnimation(anim, "pos",anim);
    rise_anim->setDuration(100);
    rise_anim->setEasingCurve(QEasingCurve::InOutQuad);
    rise_anim->setKeyValueAt(0, anim->pos());
    rise_anim->setKeyValueAt(1, anim->pos() + QPoint(0, -27));
    return rise_anim;
}
template<typename T>
QPropertyAnimation* custom_field::fall(T* anim) {
    QPropertyAnimation* fall_anim = new QPropertyAnimation(anim, "pos");
    fall_anim->setDuration(100);
    fall_anim->setEasingCurve(QEasingCurve::InOutQuad);
    fall_anim->setKeyValueAt(0, anim->pos() + QPoint(0, -27));
    fall_anim->setKeyValueAt(1, anim->pos());
    return fall_anim;
}
template<typename T>
std::vector<QPropertyAnimation*> custom_field::focus(T* anim) {
    QPropertyAnimation* rad_anim = new QPropertyAnimation(anim, "borderRadius");
    rad_anim->setDuration(200);
    rad_anim->setEasingCurve(QEasingCurve::OutInQuint);
    rad_anim->setKeyValueAt(0, 0.5);
    rad_anim->setKeyValueAt(0.5, 2.0);
    rad_anim->setKeyValueAt(1, 0.5);
    return {rad_anim};
}
void model::changeSvg(const QString& svgPath, const QColor& newColor, QLabel* label,int size) {

    QSvgRenderer svgRenderer(svgPath);
    QPixmap pixmap(size,size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    svgRenderer.render(&painter);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), newColor);
    painter.end();

    // Set the colored pixmap to a QLabel (or any widget)
    label->setPixmap(pixmap);
}

template<typename T>
QPropertyAnimation* custom_field::coloranim(T* anim, const QColor& col_from, const QColor& col_to) {
    QPropertyAnimation* col_anim = new QPropertyAnimation(anim, "borderColor");
    col_anim->setDuration(100);
    col_anim->setEasingCurve(QEasingCurve::OutInQuint);
    col_anim->setStartValue(col_from.name());
    col_anim->setEndValue(col_to.name());
    return col_anim;
}

void custom_label::enterEvent(QEnterEvent* ev){
    QLabel::enterEvent(ev);
    //qInfo() << ev->pos();
}

void custom_label::mouseMoveEvent(QMouseEvent* ev){
    QLabel::mouseMoveEvent(ev);
    //qInfo() << ev->pos();
}
