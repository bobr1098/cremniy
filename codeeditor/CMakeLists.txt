cmake_minimum_required(VERSION 3.16)

project(codeeditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# cpp
set(SRC
    QCodeEditor.cpp
    QLineNumberArea.cpp
    QCXXHighlighter.cpp
    QSyntaxStyle.cpp
    QStyleSyntaxHighlighter.cpp


    QLanguage.cpp

    QJSONHighlighter.cpp


    QPythonCompleter.cpp

    QFramedTextAttribute.cpp
)

# headers с Q_OBJECT
set(HDR
    internal/QCodeEditor.hpp
    internal/QLineNumberArea.hpp
    internal/QSyntaxStyle.hpp
    internal/QStyleSyntaxHighlighter.hpp
    internal/QCXXHighlighter.hpp


    internal/QLanguage.hpp

    internal/QJSONHighlighter.hpp


    internal/QPythonCompleter.hpp

    internal/QFramedTextAttribute.hpp
)

# .qrc ресурсы
set(QRC
    qcodeeditor_resources.qrc
)

add_library(codeeditor STATIC
    ${SRC}
    ${HDR}   # moc headers
    ${QRC}   # rcc resources
)

target_include_directories(codeeditor PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
)

target_link_libraries(codeeditor PUBLIC Qt6::Widgets)