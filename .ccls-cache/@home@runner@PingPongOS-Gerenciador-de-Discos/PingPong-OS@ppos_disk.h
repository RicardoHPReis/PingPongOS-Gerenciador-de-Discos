// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.2 -- Julho de 2017

// interface do gerente de disco rígido (block device driver)

#ifndef __DISK_MGR__
#define __DISK_MGR__
#include "ppos.h"

// estruturas de dados e rotinas de inicializacao e acesso
// a um dispositivo de entrada/saida orientado a blocos,
// tipicamente um disco rigido.

// estrutura de dados que representa um pedido de leitura/escrita ao disco
typedef struct diskrequest_t {
	struct diskrequest_t* next;
	struct diskrequest_t* prev;

	task_t* task;
	unsigned char operation; // DISK_REQUEST_READ ou DISK_REQUEST_WRITE
	int block;
	void* buffer;
} diskrequest_t;

// estrutura de dados que representa o disco
typedef struct {
	// completar com os campos necessarios
	int numBlocks;
	int blockSize;

	semaphore_t semaforo;

	unsigned char sinal;
	unsigned char livre;

	task_t* diskQueue;
	diskrequest_t* requestQueue;
} disk_t;

// inicializacao do gerente de disco
// retorna -1 em erro ou 0 em sucesso
// numBlocks: tamanho do disco, em blocos
// blockSize: tamanho de cada bloco do disco, em bytes
int disk_mgr_init (int *numBlocks, int *blockSize);

// leitura de um bloco, do disco para o buffer
int disk_block_read (int block, void *buffer);

// escrita de um bloco, do buffer para o disco
int disk_block_write (int block, void *buffer);

// escopo do driver
void diskDriverBody (void *args);

//First Come, First Served
int FCFS (int block, void *buffer);

//Shortest Seek-Time First
int SSTF (int block, void *buffer);

//Circular Scan (CSCAN)
int CSCAN (int block, void *buffer);

#endif