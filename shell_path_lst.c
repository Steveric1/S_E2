#include "shellcmd.h"
#include "shell_path.h"
#include "main.h"


/**
 * add_at_beg - Add a new node at the beginning of a linked list.
 * @headptr: Pointer to the head of the linked list.
 * @path: The string (path) to be stored in the new node.
 *
 * This function creates a new node with the provided path and inserts it at
 * the beginning of the linked list pointed to by headptr.
 *
 * Return: A pointer to the newly created node, or NULL on failure.
*/
directory_n *add_at_beg(directory_n **headptr, const char *path)
{
    directory_n *new_node;

    if (headptr == NULL)
        return (NULL);
    new_node = malloc(sizeof(directory_n));
    if (new_node == NULL)
        return (NULL);
    new_node->path = _strdup(path);
    if (new_node->path == NULL)
    {
        free_all(1, new_node);
        return (NULL);
    }
    new_node->link = *headptr;

    *headptr = new_node;
    return (new_node);
}

/**
 * dir_at_the_end - Add a new node with a path at the end of a linked list.
 * @dir_head: Pointer to the head of the linked list.
 * @path: The path to be stored in the new node.
 *
 * This function creates a new node with the provided path and appends it to
 * the end of the linked list pointed to by dir_head.
 *
 * Return: A pointer to the newly created node, or NULL on failure.
 */
directory_n *dir_at_the_end(directory_n **dir_head, const char *path)
{
    directory_n *new_node, *current;

    if (!dir_head)
        return (NULL);
    new_node = malloc(sizeof(directory_n));
    if (new_node == NULL)
       return (NULL);

    new_node->path = _strdup(path);
    
    if (new_node->path == NULL)
    {
        free_all(1, new_node);
        return (NULL);
    }
    new_node->link = NULL;

    if (!*dir_head)
       *dir_head = new_node;
    else
    {
        current = *dir_head;
        while (current->link != NULL)
            current = current->link;
        current->link = new_node;
    }
    return (new_node);
}

/**
 * free_dir - Frees the memory allocated for a directory linked list.
 * @head_ptr: A pointer to the head of the directory linked list.
 *
 * This function iterates through the directory linked list, freeing the memory
 * allocated for each path string and the corresponding nodes. It updates the
 * head pointer to the next node in each iteration until the list is empty.
 */
void free_dir(directory_n **head_ptr)
{
    directory_n *next_node;

    while (*head_ptr != NULL)
    {
        next_node = *head_ptr;
        *head_ptr = next_node->link;
        free_all(2, next_node->path, next_node);
    }
}

/**
 * path_to_list - Convert a path string into a linked list of directories.
 * @tail_ptr: A pointer to store the tail of the linked list (optional).
 * @help: A path_helper structure containing path and delimiter information.
 * Returns: A pointer to the head of the linked list on success, or NULL on failure.
 */
directory_n *path_to_list(directory_n **tail_ptr, const char *path, char delim)
{
    directory_n *head, *tail;
    ssize_t length;
    head = tail = NULL;

    while (*path)
    {
        length = _strchr(path, delim);
        if (length == -1)
            length = _strlen(path);
        
        tail = dir_at_the_end(&head, path);
        if (tail == NULL)
        {
            free_dir(&head);
            return (NULL);
        }

        tail->path = _memdup(path, length + 1);
        if (tail->path == NULL)
        {
            free_dir(&head);
            return (NULL);
        }

        tail->path[length] = '\0';
        path += length + 1;
    }

    if (tail_ptr)
        *tail_ptr = tail;
    return (head);
}

/**
 * path_wrapper - Wrapper function to create a directory list from a path string.
 * @help: A path_helper structure containing path and delimiter information.
 * Returns: A pointer to the head of the linked list on success, or NULL on failure.
 */
directory_n *path_wrapper(const char *path, char delim)
{
    directory_n *head = NULL;

    if (!path)
        return (NULL);
    
    if (!path_to_list(&head, path, delim))
        free_dir(&head);
    return (head);
}