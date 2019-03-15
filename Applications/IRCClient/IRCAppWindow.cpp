#include "IRCAppWindow.h"
#include "IRCSubWindow.h"
#include <LibGUI/GListBox.h>
#include <LibGUI/GBoxLayout.h>

IRCAppWindow::IRCAppWindow()
    : GWindow()
    , m_client("127.0.0.1", 6667)
{
    set_title(String::format("IRC Client: %s:%d", m_client.hostname().characters(), m_client.port()));
    set_rect(200, 200, 600, 400);
    setup_client();
    setup_widgets();
}

IRCAppWindow::~IRCAppWindow()
{
}

void IRCAppWindow::setup_client()
{
    m_client.on_connect = [this] {
        m_client.join_channel("#test");
    };

    m_client.on_query_message = [this] (const String& name) {
        // FIXME: Update query view.
    };

    m_client.on_channel_message = [this] (const String& channel_name) {
        // FIXME: Update channel view.
    };

    m_client.connect();
}

void IRCAppWindow::setup_widgets()
{
    auto* widget = new GWidget(nullptr);
    widget->set_fill_with_background_color(true);
    set_main_widget(widget);
    widget->set_layout(make<GBoxLayout>(Orientation::Horizontal));

    auto* subwindow_list = new GListBox(widget);
    subwindow_list->set_size_policy(SizePolicy::Fixed, SizePolicy::Fill);
    subwindow_list->set_preferred_size({ 120, 0 });
    subwindow_list->add_item("test1");
    subwindow_list->add_item("test2");
    subwindow_list->add_item("test3");

    auto* container = new GWidget(widget);

    auto* subwindow = new IRCSubWindow("Server", container);
}