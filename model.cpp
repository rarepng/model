#include "model.hpp"

#include <iostream>
#include <qfile.h>





model::model(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);




    QImage body{ "body.png" };


    body.convertToFormat(QImage::Format_RGBA8888);

    total_assets = new custom_field("Total Assets", false, ui.assets_label);
    total_revenue = new custom_field("Total Revenue", false, ui.revenue_label);
    total_marketing_cost = new custom_field("Total Marketing Costs", false, ui.marketingcost_label);
    total_salaries = new custom_field("Total Salaries", false, ui.salaries_label);
    cogs_perc = new custom_field("COGS %", false, ui.cogsperc_label);
    cogs_value = new custom_field("COGS Value", false, ui.cogsvalue_label);
    total_expenses = new custom_field("Total Expenses", false, ui.expenses_label);


    total_assets->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    total_revenue->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    total_marketing_cost->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    total_salaries->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    cogs_perc->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    cogs_value->setValidator(new QDoubleValidator(0, 100.0, 2, this));
    total_expenses->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));



    body_label = new custom_label(body,ui.body);



    submit = new custom_button(ui.update_label);
    connect(reinterpret_cast<QPushButton*>(submit), &QAbstractButton::clicked, this, &model::updateallcols);
    reset = new custom_button(ui.reset_label);
    connect(reinterpret_cast<QPushButton*>(reset), &QAbstractButton::clicked, this, &model::resetcols);

}







void model::updateheartcol(int value) {
    //heart_hue = value;
    //changeSvg("heart.svg", QColor::fromHsv(value, 255, 255), ui.heart, heart_size);
}
void model::updatebraincol(int value) {
    //brain_hue = value;
    //changeSvg("brain.svg", QColor::fromHsv(value, 255, 255), ui.brain, brain_size);
}
void model::updateheartsize(int value) {
    //heart_size = value;
    //changeSvg("heart.svg", QColor::fromHsv(heart_hue, 255, 255), ui.heart, value);
}
void model::updatebrainsize(int value) {
    //brain_size = value;
    //changeSvg("brain.svg", QColor::fromHsv(brain_hue, 255, 255), ui.brain, value);
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
    this->orig = img;

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
        for (int i{ mouseEvent->pos().x() }; i < mouseEvent->pos().x() + 20; i++) {
            for (int j{ mouseEvent->pos().y() }; j < mouseEvent->pos().y() + 20; j++) {
                QColor c = this->bodyimg.pixelColor(i, j);

                c.setHsv(0, c.saturation(), c.value(), c.alpha());
                this->bodyimg.setPixelColor(i, j, c);
            }
        }
        this->setPixmap(QPixmap::fromImage(this->bodyimg));
        //qInfo() << mouseEvent->pos();
    }
    return false;
}

void custom_label::rerender(){
    this->setPixmap(QPixmap::fromImage(this->bodyimg));
}

void custom_label::reset(){
    this->setPixmap(QPixmap::fromImage(this->orig));
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

void model::updateallcols() {
    for (const auto& i : parts) {
        for (int j{ i.startx }; j < i.startx+i.width; j++) {
            for (int k{ i.starty }; k < i.starty+i.height; k++) {
                QColor c = this->body_label->bodyimg.pixelColor(j, k);
                int sat = static_cast<int>(255.0f * (1.0f - std::sqrt(std::pow((static_cast<float>(j - i.startx) / static_cast<float>(i.width)) - 0.5, 2) + std::pow((static_cast<float>(k - i.starty) / static_cast<float>(i.height)) - 0.5, 2))));
                //c.setHsv(i.hue + 255 - (sat), sat, c.value(), c.alpha());
                c.setHsv(i.hue(), sat, c.value(), c.alpha());
                this->body_label->bodyimg.setPixelColor(j, k, c);
            }
        }
    }
    this->body_label->rerender();
}

void model::resetcols(){
    this->body_label->reset();
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

custom_button::custom_button(QWidget* parent) : QPushButton(parent){
    this->installEventFilter(this);
    this->mapToParent(QPoint(0, 0));

    this->setGeometry(parent->rect());
}

