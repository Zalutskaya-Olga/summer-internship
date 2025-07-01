/****************************************************************************
** Meta object code from reading C++ file 'emotiondetector.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../emotiondetector.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emotiondetector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15EmotionDetectorE_t {};
} // unnamed namespace

template <> constexpr inline auto EmotionDetector::qt_create_metaobjectdata<qt_meta_tag_ZN15EmotionDetectorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "EmotionDetector",
        "Emotion",
        "Neutral",
        "Happy",
        "Sad",
        "Angry",
        "Excited",
        "Calm",
        "Fear",
        "Disgust",
        "Surprise"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Emotion'
        QtMocHelpers::EnumData<Emotion>(1, 1, QMC::EnumFlags{}).add({
            {    2, Emotion::Neutral },
            {    3, Emotion::Happy },
            {    4, Emotion::Sad },
            {    5, Emotion::Angry },
            {    6, Emotion::Excited },
            {    7, Emotion::Calm },
            {    8, Emotion::Fear },
            {    9, Emotion::Disgust },
            {   10, Emotion::Surprise },
        }),
    };
    return QtMocHelpers::metaObjectData<EmotionDetector, qt_meta_tag_ZN15EmotionDetectorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject EmotionDetector::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15EmotionDetectorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15EmotionDetectorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15EmotionDetectorE_t>.metaTypes,
    nullptr
} };

void EmotionDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EmotionDetector *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *EmotionDetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmotionDetector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15EmotionDetectorE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EmotionDetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
