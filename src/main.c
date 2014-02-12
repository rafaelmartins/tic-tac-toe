/*
 * tic-tac-toe: A simple Tic Tac Toe webapp using balde microframework.
 * Copyright (C) 2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the LGPL-2 License.
 * See the file COPYING.
 */

#include <balde.h>
#include <json-glib/json-glib.h>


typedef enum {
    TTT_EMPTY,
    TTT_X,
    TTT_O,
} ttt_mark_t;


typedef struct {
    ttt_mark_t marks[3][3];
} ttt_board_t;


const gchar*
ttt_mark_to_str(ttt_mark_t mark)
{
    switch (mark) {
        case TTT_EMPTY:
            return "";
        case TTT_X:
            return "X";
        case TTT_O:
            return "O";
    }
    return NULL;
}


gchar*
ttt_board_to_json(ttt_board_t *board)
{
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "board");
    json_builder_begin_array(builder);
    for (guint i = 0; i < 3; i++) {
        json_builder_begin_array(builder);
        for (guint j = 0; j < 3; j++) {
            json_builder_add_string_value(builder,
                ttt_mark_to_str(board->marks[i][j]));
        }
        json_builder_end_array(builder);
    }
    json_builder_end_array(builder);
    json_builder_end_object(builder);
    JsonGenerator *gen = json_generator_new();
    JsonNode * root = json_builder_get_root(builder);
    json_generator_set_root(gen, root);
    gchar *str = json_generator_to_data(gen, NULL);
    json_node_free(root);
    g_object_unref(gen);
    g_object_unref(builder);
    return str;
}


gchar*
ttt_error_to_json(const gchar *error)
{
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "error");
    json_builder_add_string_value(builder, error);
    json_builder_end_object(builder);
    JsonGenerator *gen = json_generator_new();
    JsonNode * root = json_builder_get_root(builder);
    json_generator_set_root(gen, root);
    gchar *str = json_generator_to_data(gen, NULL);
    json_node_free(root);
    g_object_unref(gen);
    g_object_unref(builder);
    return str;
}





balde_response_t*
board(balde_app_t *app, balde_request_t *request)
{
    ttt_board_t *board = g_new(ttt_board_t, 1);
    board->marks[0][0] = TTT_X;
    board->marks[0][1] = TTT_X;
    board->marks[0][2] = TTT_X;
    board->marks[1][0] = TTT_O;
    board->marks[1][1] = TTT_O;
    board->marks[1][2] = TTT_O;
    board->marks[2][0] = TTT_EMPTY;
    board->marks[2][1] = TTT_X;
    board->marks[2][2] = TTT_X;
    gchar *str = ttt_board_to_json(board);
    balde_response_t *rv = balde_make_response(ttt_board_to_json(board));
    balde_response_set_header(rv, "Content-Type", "application/json");
    g_free(str);
    g_free(board);
    return rv;
}


int
main(int argc, char **argv)
{
    balde_app_t *app = balde_app_init();
    balde_app_add_url_rule(app, "board", "/board/", BALDE_HTTP_GET, board);
    balde_app_run(app);
    balde_app_free(app);
}
