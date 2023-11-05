#include "../include/paging.h"

static page_directory_t *current_page_directory;
static page_directory_t *kernel_directory;
static page_directory_t page_directory_pool[1024];
