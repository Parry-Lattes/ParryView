#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <type_traits>

#include <webview/webview.h>
#include <nlohmann/json.hpp>
#include <battery/embed.hpp>

static const std::string initialPage = R"(https://buscatextual.cnpq.br/buscatextual/busca.do?metodo=apresentar)";
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

    webview_t webview = webview_create(true, nullptr);
    webview_set_title(webview, "ParryView");
    webview_navigate(webview, initialPage.c_str());

    // webview_bind(webview, "saveHTMLPage", SaveHTMLPage, &webview);
    webview_init(webview, b::embed<"test.js">().data());

    webview_run(webview);

    webview_destroy(webview);
    return 0;
}