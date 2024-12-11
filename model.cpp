                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        #include "model.hpp"

#include <iostream>
#include <qfile.h>





model::model(QWidget* parent) : QMainWindow(parent) {

    ui.setupUi(this);



    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.0);


    ui.hover_head_label->setGraphicsEffect(effect);
    ui.hover_heart_label->setGraphicsEffect(effect);
    ui.hover_arms_label->setGraphicsEffect(effect);
    ui.hover_torso_label->setGraphicsEffect(effect);
    ui.hover_legs_label->setGraphicsEffect(effect);
    ui.hover_hands_label->setGraphicsEffect(effect);

    ui.hover_head_label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui.hover_heart_label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui.hover_arms_label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui.hover_torso_label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui.hover_legs_label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui.hover_hands_label->setAttribute(Qt::WA_TransparentForMouseEvents, true);


    ui.hover_head_label->setAttribute(Qt::WA_NoSystemBackground, true);
    ui.hover_heart_label->setAttribute(Qt::WA_NoSystemBackground, true);
    ui.hover_arms_label->setAttribute(Qt::WA_NoSystemBackground, true);
    ui.hover_torso_label->setAttribute(Qt::WA_NoSystemBackground, true);
    ui.hover_legs_label->setAttribute(Qt::WA_NoSystemBackground, true);
    ui.hover_hands_label->setAttribute(Qt::WA_NoSystemBackground, true);













    QImage body{ "body.png" };


    body = body.convertToFormat(QImage::Format_RGBA8888);

    total_assets = new custom_field("Total Assets", false, ui.assets_label);
    total_revenue = new custom_field("Total Revenue", false, ui.revenue_label);
    total_marketing_cost = new custom_field("Total Marketing Costs", false, ui.marketingcost_label);
    total_salaries = new custom_field("Total Salaries", false, ui.salaries_label);
    cogs_perc = new custom_field("COGS %", false, ui.cogsperc_label);
    cogs_value = new custom_field("COGS Value", false, ui.cogsvalue_label);
    total_expenses = new custom_field("Total Expenses", false, ui.expenses_label);

    employees_left = new custom_field("Employees left",false,ui.employees_left_label);
    average_total_employees = new custom_field("Average total employees",false,ui.Average_total_employees_label);
    total_units = new custom_field("Total units",false,ui.total_units_label);
    production_hour = new custom_field("Production hour",false,ui.production_hour_label);
    material_cost = new custom_field("Material cost",false,ui.material_cost_label);
    marketing_cost = new custom_field("Marketing cost",false,ui.marketing_cost_label);
    new_products = new custom_field("New products",false,ui.new_products_label);
    total_products = new custom_field("Total products",false,ui.total_products_label);
    current_revenue = new custom_field("Current revenue",false,ui.current_revenue_label);
    previous_revenue = new custom_field("previous revenue", false, ui.previous_revenue_label);






    total_assets->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    total_revenue->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    total_marketing_cost->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    total_salaries->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    cogs_perc->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    cogs_value->setValidator(new QDoubleValidator(0, 100.0, 2, this));
    total_expenses->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));





    employees_left->setValidator(new QIntValidator(0, 1'000'000'000, this));
    average_total_employees->setValidator(new QIntValidator(0, 1'000'000'000, this));
    total_units->setValidator(new QIntValidator(0, 1'000'000'000, this));
    production_hour->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    material_cost->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    marketing_cost->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    new_products->setValidator(new QIntValidator(0, 1'000'000'000, this));
    total_products->setValidator(new QIntValidator(0, 1'000'000'000, this));
    current_revenue->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));
    previous_revenue->setValidator(new QDoubleValidator(0, 1'000'000'000'000.0, 2, this));




    body_label = new custom_label(body, ui.body);



    submit = new custom_button("Calculate all", ui.update_label);
    connect(reinterpret_cast<QPushButton*>(submit), &QAbstractButton::clicked, this, &model::updateallcols);
    reset = new custom_button("reset all", ui.reset_label);
    connect(reinterpret_cast<QPushButton*>(reset), &QAbstractButton::clicked, this, &model::resetcols);





    stomach_hover = new custom_hoverbox(msgstomach, ui.hover_stomach_label);
    head_hover = new custom_hoverbox(msghead, ui.hover_head_label);
    heart_hover = new custom_hoverbox(msgheart, ui.hover_heart_label);
    arms_hover = new custom_hoverbox(msgarms, ui.hover_arms_label);
    torso_hover = new custom_hoverbox(msgtorso, ui.hover_torso_label);
    legs_hover = new custom_hoverbox(msglegs, ui.hover_legs_label);
    hands_hover = new custom_hoverbox(msghands, ui.hover_arms_label);





    
    //ui.setupUi(this);

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

bool custom_label::eventFilter(QObject* obj, QEvent* ev) {
    //if (ev->type() == QEvent::MouseMove) {
    //    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(ev);
    //    for (int i{ mouseEvent->pos().x() }; i < mouseEvent->pos().x() + 20; i++) {
    //        for (int j{ mouseEvent->pos().y() }; j < mouseEvent->pos().y() + 20; j++) {
    //            QColor c = this->bodyimg.pixelColor(i, j);

    //            c.setHsv(0, c.saturation(), c.value(), c.alpha());
    //            this->bodyimg.setPixelColor(i, j, c);
    //        }
    //    }
    //    this->setPixmap(QPixmap::fromImage(this->bodyimg));
    //}

    if (ev->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(ev);
        for (const auto& r : model::parts) {
                r.hide();
        }
        for (const auto& r : model::parts2) {
                r.hide();
        }
        for (const auto& r : model::parts) {
            if (r.dim.contains(mouseEvent->pos())) {
                r.disp();
            }
        }
        for (const auto& r : model::parts2) {
            if (r.dim.contains(mouseEvent->pos())) {
                r.disp();
            }
        }
    }


    if (ev->type() == QEvent::Leave) {
        for (const auto& r : model::parts) {
            r.hide();
        }
        for (const auto& r : model::parts2) {
            r.hide();
        }
    }
        //qInfo() << mouseEvent->pos();
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

void custom_button::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    qInfo() << "resize";
    QRect tmp = ((QWidget*)this->parent())->rect();
}
void model::updateallcols() {
    for (const auto& i : parts) {
        for (int j{ i.dim.x()}; j < (i.dim.x() + i.dim.width()); j++) {
            for (int k{ i.dim.y()}; k < (i.dim.y() + i.dim.height()); k++) {
                QColor c = this->body_label->bodyimg.pixelColor(j, k);
                int sat = static_cast<int>(255.0f * (1.0f - std::sqrt(std::pow((static_cast<float>(j - i.dim.x()) / static_cast<float>(i.dim.width())) - 0.5, 2) + std::pow((static_cast<float>(k - i.dim.y()) / static_cast<float>(i.dim.height())) - 0.5, 2))));
                c.setHsv(i.hue(i.huefn()), sat, c.value(), c.alpha());
                this->body_label->bodyimg.setPixelColor(j, k, c);
            }
        }
    }
    this->body_label->rerender();


    for (const auto& i : parts2) {
        for (int j{ i.dim.x() }; j < (i.dim.x() + i.dim.width()); j++) {
            for (int k{ i.dim.y() }; k < (i.dim.y() + i.dim.height()); k++) {
                QColor c = this->body_label->bodyimg.pixelColor(j, k);
                int sat = std::clamp(static_cast<int>(255.0f * (1.0f - std::sqrt(std::pow((static_cast<float>(j - i.dim.x()) / static_cast<float>(i.dim.width())) - 0.5, 2) + std::pow((static_cast<float>(k - i.dim.y()) / static_cast<float>(i.dim.height())) - 0.5, 2)))),0,255);
                //if(sat>128)c.setHsv(static_cast<int>((i.hue(i.huefn())*((sat) / 200))+(c.hue()*(1 - ((sat) / 200)))), c.saturation(), c.value(), c.alpha());
                //if (sat > 128)c.setHsv(((i.hue(i.huefn())* (sat-128)/64)+(c.hue())*(1 - (sat-128)/64))/2, (c.saturation() + sat) / 2, c.value(), c.alpha());
                if (sat > 128)c.setHsv(i.hue(i.huefn()), (c.saturation() + sat) / 2, c.value(), c.alpha());
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

custom_button::custom_button(QString placeholder,QWidget* parent) : QPushButton(parent){
    this->installEventFilter(this);
    this->mapToParent(QPoint(0, 0));
    this->setText(placeholder);
    this->setStyleSheet("QPushButton{\
        padding:20px 16px 20px 16px;\
        margin:16px;\
        color: white;\
            background-color: blue;\
            border-radius: 20px;\
            font-weight: Medium;\
        }\
        QPushButton:hover{\
        border: 2px solid red;\
        }\
        QPushButton:pressed{\
        background-color: #0063c5;\
        }\
        QPushButton:disabled{\
        background-color: grey;\
        }\
        QPushButton:focused{\
        border: 2px solid red;\
        }\
        QPushButton:!active{\
        background-color: grey;\
    }");
    this->setGeometry(parent->rect());
}


custom_hoverbox::custom_hoverbox(QString msg, QWidget* parent) : QLabel(parent) {

    this->installEventFilter(this);

    this->mapToParent(QPoint(0, 0));

    this->setGeometry(parent->rect());

    this->setText("<h1 style=\"color: red; font-family: Arial, sans-serif; font-size: 36px; text-align: center;\">50%</h1>" +msg);


    this->setStyleSheet("background-color: rgba(0, 0, 0, 255); border: 2px solid white; padding: 10px;    QLabel h1 {\
        background-color: red;\
} ");

    this->setProperty("wordWrap", true);

    this->adjustSize();
    //parent->setMouseTracking(true);
    this->setVisible(false);
    this->setHidden(true);
    this->parentWidget()->setVisible(false);
    this->parentWidget()->setHidden(true);

}
void custom_hoverbox::visible2() {

    this->setVisible(true);
    this->setHidden(false);
    this->parentWidget()->setVisible(true);
    this->parentWidget()->setHidden(false);

}
void custom_hoverbox::visiblefalse() {

    this->setVisible(false);
    this->setHidden(true);
    this->parentWidget()->setVisible(false);
    this->parentWidget()->setHidden(true);

}
