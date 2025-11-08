#include <iostream>
#include <fstream>
#include <filesystem>

#include <webview/webview.h>
#include <nlohmann/json.hpp>
#include <battery/embed.hpp>

static const std::string ROOT_URL = R"(http://lattes.cnpq.br/)";

namespace fs = std::filesystem;

struct GlobalContext
{
    webview_t webview = nullptr;
} context;

void SaveHTMLPage(const char* id, const char* req, void* arg)
{
    nlohmann::json reqJsonArr = nlohmann::json::parse(req);

    std::string html = reqJsonArr[0].get<std::string>();

    // Remove tabs and newlines from original html;
    html.erase(std::ranges::remove(html, '\t').begin(), html.end());
    html.erase(std::ranges::remove(html, '\n').begin(), html.end());

    std::cout << html << std::endl;
}

void Shutdown()
{
    webview_destroy(context.webview);
    context.webview = nullptr;
}

int main(const int argc, char* argv[])
{
    if (atexit(Shutdown) != 0)
    {
        return EXIT_FAILURE;
    }

    if (argc == 1)
    {
        std::cerr << "Usage: " << argv[0] << " {IdLattes}" << std::endl;
        return -1;
    }


    context.webview = webview_create(
#ifdef NDEBUG
    false,
#else
    true,
#endif
        nullptr
        );
    webview_set_title(context.webview, "ParryView");
    webview_navigate(context.webview, (ROOT_URL + argv[1]).c_str());

    webview_bind(context.webview, "saveHTMLPage", SaveHTMLPage, nullptr);
    webview_init(context.webview, b::embed<"test.js">().data());

    webview_run(context.webview);

    return EXIT_SUCCESS;
}