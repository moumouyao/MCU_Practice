/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
/* ���ǿ�����ӵĺ궨�� */
#define configUSE_TIME_SLICING 1 //ʹ��ʱ��Ƭ����(Ĭ��ʽʹ�ܵ�)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1 //Ӳ������ǰ����ָ������ʹ�õģ� MCU û����ЩӲ��ָ��Ļ��˺�Ӧ������Ϊ 0
#define configUSE_TICKLESS_IDLE 0 //�� 1��ʹ�ܵ͹��� tickless ģʽ���� 0������ϵͳ���ģ� tick���ж�һֱ����
#define configUSE_QUEUE_SETS 1 //���ö��м�
#define configUSE_TASK_NOTIFICATIONS 1 //��������֪ͨ���ܣ�Ĭ�Ͽ���
#define configUSE_MUTEXES 1 //ʹ�û����ź���
#define configUSE_RECURSIVE_MUTEXES 1 //ʹ�õݹ黥���ź���
#define configUSE_COUNTING_SEMAPHORES 1 //Ϊ 1 ʱʹ�ü����ź���
#define configQUEUE_REGISTRY_SIZE 10 //���ÿ���ע����ź�������Ϣ���и���
#define configUSE_APPLICATION_TASK_TAG 0
#define configSUPPORT_DYNAMIC_ALLOCATION 1 //֧�ֶ�̬�ڴ�����
//#define configSUPPORT_STATIC_ALLOCATION	 1 //֧�־�̬�����ڴ�
#define configUSE_MALLOC_FAILED_HOOK 0 //ʹ���ڴ�����ʧ�ܹ��Ӻ���
#define configCHECK_FOR_STACK_OVERFLOW 1// ���� 0 ʱ���ö�ջ�����⹦�ܣ����ʹ�ô˹����û������ṩһ��ջ������Ӻ������ʹ�õĻ���ֵ����Ϊ 1 ���� 2����Ϊ������ջ�����ⷽ��
#define configGENERATE_RUN_TIME_STATS 0 //��������ʱ��ͳ�ƹ���
#define configUSE_STATS_FORMATTING_FUNCTIONS 1
#define configUSE_TIMERS 1 //���������ʱ��
#define configTIMER_TASK_PRIORITY (configMAX_PRIORITIES-1) //�����ʱ�����ȼ�
#define configTIMER_QUEUE_LENGTH 10 //�����ʱ�����г���
#define configTIMER_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE*2) //�����ʱ�������ջ��С

//��ѡ��������ѡ��
#define INCLUDE_xTaskGetSchedulerState 1
#define INCLUDE_eTaskGetState 1
#define INCLUDE_xTimerPendFunctionCall 1

//�жϷ����� Ҳ�����޸���ʼ�ļ�
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler




#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			0
#define configCPU_CLOCK_HZ			( ( unsigned long ) 72000000 )	
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES		( 5 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )	//���������ջ�ռ�
#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 17 * 1024 ) )
#define configMAX_TASK_NAME_LEN		( 16 )
#define configUSE_TRACE_FACILITY	0
#define configUSE_16_BIT_TICKS		0
#define configIDLE_SHOULD_YIELD		1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1					//�����������
#define INCLUDE_xTaskResumeFromISR  1				//�����������жϷ������лָ�
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
(lowest) to 0 (1?) (highest). */
#define configKERNEL_INTERRUPT_PRIORITY 		255
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	0x50 /* equivalent to 0xb0, or priority 11. */


/* This is the value being used as per the ST library which permits 16
priority values, 0 to 15.  This must correspond to the
configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
NVIC value of 255. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15
//#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY  5      /* FreeRTOS�ɹ��������ж����ȼ� */ 
        

#endif /* FREERTOS_CONFIG_H */

