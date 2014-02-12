/*
 * tic-tac-toe: A simple Tic Tac Toe webapp using balde microframework.
 * Copyright (C) 2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the LGPL-2 License.
 * See the file COPYING.
 */

#include <balde.h>


balde_response_t*
home(balde_app_t *app, balde_request_t *request)
{
    return balde_make_response("Hello World! I'm the balde! :D");
}


int
main(int argc, char **argv)
{
    balde_app_t *app = balde_app_init();
    balde_app_add_url_rule(app, "home", "/", BALDE_HTTP_GET, home);
    balde_app_run(app);
    balde_app_free(app);
}
