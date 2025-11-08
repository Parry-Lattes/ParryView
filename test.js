const COMPARISON_URL = "http://buscatextual.cnpq.br/buscatextual/visualizacv.do"

window.addEventListener('load', () => {
    if (
        !window.location.href.includes(COMPARISON_URL)
        || document.querySelector('#divCaptcha')
    ) {
        return;
    }

    saveHTMLPage(document.documentElement.outerHTML);
}, {once: true})