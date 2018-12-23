//
// Created by davide on 10/12/18.
//

typedef struct Tree {
    //char *value;
    char value[100];
    int occurrences;
    struct Tree *left;
    struct Tree *right;
} Tree;




/*
 * void node_print(NodePtr node_ptr, int occ) {
    char* str = malloc(sizeof(char *));
    if (node_ptr != NULL) {
        node_print(node_ptr->left, occ);
        if(occ == 0){
            sprintf(str, "%s %i\n", node_ptr->word, node_ptr->count);
            write_file(str);
        }
        else {
            if (node_ptr->count == occ) {
                sprintf(str, "%s %i\n", node_ptr->word, node_ptr->count);
                write_file(str);
            }
        }
        node_print(node_ptr->right, occ);
    }
}
* */

