// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.2 -- Julho de 2017

// interface do gerente de disco rígido (block device driver)

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "ppos_disk.h"
#include "disk.h"

//struct sigaction action;

// inicializacao do gerente de disco
// retorna -1 em erro ou 0 em sucesso
// numBlocks: tamanho do disco, em blocos
// blockSize: tamanho de cada bloco do disco, em bytes
int disk_mgr_init (int *numBlocks, int *blockSize)
{
	int iniciou = disk_cmd (DISK_CMD_INIT, 0, 0);

	if(iniciou == 0)
	{
		*blockSize = disk_cmd (DISK_CMD_DISKSIZE, 0, 0);
	
		*numBlocks = disk_cmd (DISK_CMD_BLOCKSIZE, 0, 0);
		
		printf("numBlocks: %d\nblockSize: %d\n", *numBlocks, *blockSize);
		
		if(*numBlocks > 0 && *blockSize > 0)
			return 0;
	}
	return -1;
}

// leitura de um bloco, do disco para o buffer
int disk_block_read (int block, void *buffer)
{
	if(disk_cmd (DISK_CMD_STATUS, 0, 0) == 1)
	{
		// obtém o semáforo de acesso ao disco
		
		// inclui o pedido na fila_disco
		disk_cmd (DISK_CMD_READ, block, buffer);
		
		if (/*gerente de disco está dormindo*/)
		{
			//acorda o gerente de disco (põe ele na fila de prontas)
		}
		
		// libera semáforo de acesso ao disco
		
		// suspende a tarefa corrente (retorna ao dispatcher)
	}
}

// escrita de um bloco, do buffer para o disco
int disk_block_write (int block, void *buffer)
{
	printf("Algo 3\n");
	
	if(disk_cmd (DISK_CMD_STATUS, 0, 0) == 1)
	{
		// obtém o semáforo de acesso ao disco

		// inclui o pedido na fila_disco
		disk_cmd (DISK_CMD_WRITE, block, buffer);

		if (/*gerente de disco está dormindo*/)
		{
			//acorda o gerente de disco (põe ele na fila de prontas)
		}

		// libera semáforo de acesso ao disco

		// suspende a tarefa corrente (retorna ao dispatcher)
	}
}

void diskDriverBody (void * args)
{
	while (1==1) 
	{
		// obtém o semáforo de acesso ao disco
		
		// se foi acordado devido a um sinal do disco
		if (/*disco gerou um sinal*/)
		{
			// acorda a tarefa cujo pedido foi atendido
		}

	  	// se o disco estiver livre e houver pedidos de E/S na fila
	  	if (disk_cmd (DISK_CMD_STATUS, 0, 0) == 1 && (fila_disco != NULL))
	  	{
			// escolhe na fila o pedido a ser atendido, usando FCFS
			// solicita ao disco a operação de E/S, usando disk_cmd()
	  	}

		// libera o semáforo de acesso ao disco

		// suspende a tarefa corrente (retorna ao dispatcher)
	}
}

//First Come, First Served
int FCFS (int block, void *buffer)
{
	
}

//Shortest Seek-Time First
int SSTF (int block, void *buffer)
{
	
}

//Circular Scan (CSCAN)
int CSCAN (int block, void *buffer)
{
	
}