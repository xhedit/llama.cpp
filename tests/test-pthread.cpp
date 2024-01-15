#include <cstdio>
#include <pthread.h>

#include "llama.h"

void * llamacpp_pthread(void * arg) {
    (void)arg;

    llama_backend_init(false);
    auto * model = llama_load_model_from_file("/Users/vczf/models/gguf-hf/TheBloke_Llama-2-7B-GGUF/llama-2-7b.Q2_K.gguf", llama_model_default_params());
    auto * ctx = llama_new_context_with_model(model, llama_context_default_params());
    llama_free(ctx);
    llama_free_model(model);
    llama_backend_free();

    return NULL;
}

// This creates a new context inside a pthread and then tries to exit
// cleanly.
int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, llamacpp_pthread, NULL);
    pthread_join(tid, NULL);
}

