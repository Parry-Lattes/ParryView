#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <type_traits>

#include <webview/webview.h>
#include <nlohmann/json.hpp>

#define JS_CODE "window.addEventListener('load', event => {" \
    "   if (document.querySelector('#divCaptcha')) return;"\
    "   saveHTMLPage(document.documentElement.outerHTML)" \
    "}, {once: true})" \

static const std::string rootUrl = R"(http://lattes.cnpq.br/)";

namespace fs = std::filesystem;

void SaveHTMLPage(const char* id, const char* req, void* arg)
{
    webview_t& webview = *static_cast<webview_t*>(arg);
    nlohmann::json reqJsonArr = nlohmann::json::parse(req);

    std::string html = reqJsonArr[0].get<std::string>();

    // Remove tabs and newlines from original html;
    html.erase(std::ranges::remove(html, '\t').begin(), html.end());
    html.erase(std::ranges::remove(html, '\n').begin(), html.end());

    std::cout << html << std::endl;

    webview_terminate(webview);
}

int main(int argc, char* argv[])
{
    static_assert(std::is_standard_layout_v<std::string> == true);

    if (argc == 1)
    {
        std::cerr << "Usage: " << argv[0] << " {idLattes}" << std::endl;
        return -1;
    }

    const std::string url = rootUrl + argv[1];

    webview_t webview = webview_create(true, nullptr);
    webview_set_title(webview, "ParryView");
    webview_navigate(webview, url.c_str());

    webview_bind(webview, "saveHTMLPage", SaveHTMLPage, &webview);
    webview_init(webview, JS_CODE);

    webview_run(webview);

    webview_destroy(webview);
    return 0;
}