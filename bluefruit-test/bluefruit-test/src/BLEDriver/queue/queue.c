/*
 * queue.c
 *
 */

#include "queue.h"

queue_index_t queue_getIndex(queue_t* q, queue_index_t index);
void queue_incrementIndexIn(queue_t* q);
void queue_incrementIndexOut(queue_t* q);

// ----------------------------------------------------------------------------

void queue_init(queue_t* q, queue_size_t size) {
    q->indexIn = 0;
    q->indexOut = 0;
    q->elementCount = 0;
    q->size = size;
    q->data = (queue_data_t *)malloc(size * sizeof(queue_data_t));
    memset(q->data, 0, size * sizeof(queue_data_t));
}

// ----------------------------------------------------------------------------

queue_size_t queue_size(queue_t* q) {
    return q->size;
}

// ----------------------------------------------------------------------------

bool queueFull(queue_t* q) {
    return (q->elementCount == queue_size(q));
}

// ----------------------------------------------------------------------------

bool queue_empty(queue_t* q) {
    return !q->elementCount;
}

// ----------------------------------------------------------------------------

void queue_push(queue_t* q, queue_data_t value) {
    if (queueFull(q)) {
        // error
    } else {
        q->data[q->indexIn] = value;
        queue_incrementIndexIn(q);

        // added an element, increase count
        ++q->elementCount;
    }
}

// ----------------------------------------------------------------------------

queue_data_t queue_pop(queue_t* q) {
    if (!queue_empty(q)) {
        queue_data_t tmp = q->data[q->indexOut];
        queue_incrementIndexOut(q);

        // removed an element, so decrease count
        --q->elementCount;

        return tmp;
    } else {
        // there is nothing to pop
        return 0;
    }
}

// ----------------------------------------------------------------------------

void queue_overwritePush(queue_t* q, queue_data_t value) {
    if (queueFull(q)) {
        q->data[q->indexIn] = value;
        queue_incrementIndexIn(q);

        // This is the "overwrite" part -- it pushes everything forward
        queue_incrementIndexOut(q);
    } else {
        // queue isn't full... call the normal implementation!
        queue_push(q, value);
    }
}

// ----------------------------------------------------------------------------

queue_data_t queue_readElementAt(queue_t* q, queue_index_t index) {
    queue_index_t realIndex = queue_getIndex(q, index);
    return q->data[realIndex];
}

// ----------------------------------------------------------------------------

queue_size_t queue_elementCount(queue_t* q) {
    return q->elementCount;
}

// ----------------------------------------------------------------------------

// Just free the malloc'd storage.
void queue_garbageCollect(queue_t* q) {
    free(q->data);
}

// ----------------------------------------------------------------------------

void queue_print(queue_t* q) {
    printf("***********************\n\r");
    printf("*** Printing Queue: ***\n\r");
    printf("***********************\n\r\n\r");

    printf("\t+ Size:\t\t %u\n\r", q->size);
    printf("\t+ Element Count: %u\n\r", q->elementCount);
    printf("\t+ Index In:\t %u\n\r", q->indexIn);
    printf("\t+ Index Out:\t %u\n\r", q->indexOut);
    printf("\t+ Queue Full?:\t %s\n\r", queueFull(q) ? "true" : "false");
    printf("\t+ Queue Empty?:\t %s\n\r\n\r", queue_empty(q) ? "true" : "false");

    printf("**** DATA ****\n\r");

    uint32_t i;
    for (i=0; i<q->size; ++i) {
        printf("[%u]   %f", i, q->data[i]);

        if (q->indexIn == i) printf("\t<- indexIn");
        if (q->indexOut == i) printf("\t<- indexOut");

        printf("\n\r");
    }

}

// ----------------------------------------------------------------------------

#define QUEUE_TEST_SIZE         5
#define QUEUE_TEST_SIZE_PART    3
#define QUEUE_DEBUG_PRINT       true
int queue_runTest() {
    printf("** runTest: Creating a Queue of size %u **\n\r", QUEUE_TEST_SIZE);

    // Initialize the Queue!
    queue_t q;
    queue_init(&q, QUEUE_TEST_SIZE);

    // test variables
    queue_index_t i;
    queue_data_t tmp = 0;


    ////////////////////////////
    //  Try popping when the  //
    //     queue is empty     //
    ////////////////////////////
    printf("- It should not pop anything, because it's empty...");
    tmp = queue_pop(&q);
    if (QUEUE_DEBUG_PRINT) queue_print(&q);
    if (tmp) {
        printf("failed. (should not have popped)\n\r");
        return QUEUE_FAIL;
    }

    printf("passed.\r\n");

    ////////////////////////////
    // Test pushing part way, //
    //    and then poping     //
    ////////////////////////////
    printf("- It should push part way, then pop once...");
    if (!queue_empty(&q)) {
        printf("failed. (should have been empty)\n\r");
        return QUEUE_FAIL;
    }
    for (i=0; i<QUEUE_TEST_SIZE_PART; ++i) {
        if (i) {
            // last element should be equal to (i-1)
            if (queue_readElementAt(&q, (i-1)) != (i-1)) {
                printf("failed. (not pushing correctly [i=%u])\n\r",i);
                return QUEUE_FAIL;
            }
        }
        queue_push(&q, i);

        if (QUEUE_DEBUG_PRINT) queue_print(&q);
    }

    // Now pop once
    tmp = queue_pop(&q);

    if (QUEUE_DEBUG_PRINT) queue_print(&q);

    // tmp should be the same as the current i value
    if (tmp != 0) {
        printf("failed. (not popping correctly [i=%u])\n\r", i);
        return QUEUE_FAIL;
    }

    printf("passed.\r\n");

    //////////////////////////
    //  Fill up the queue,  //
    // and test wrap around //
    //////////////////////////
    printf("- It should push all the way, then wrap around...");
    for (; i<(queue_size(&q)+1); ++i) {
        queue_push(&q, i);
        if (QUEUE_DEBUG_PRINT) queue_print(&q);
    }

    if (!queueFull(&q)) {
        printf("failed. (should be full)\n\r");
        return QUEUE_FAIL;
    }

    // Test that queue_push doesn't do anything when full
    queue_index_t tmp_indexIn = q.indexIn;
    queue_push(&q, (double)i+0.5f);
    if (tmp_indexIn != q.indexIn) {
        printf("failed. (should not have pushed)\n\r");
        return QUEUE_FAIL;
    }

    // push and overwrite (since it's wrapped)
    queue_overwritePush(&q, (double)i+0.5f);
    if (QUEUE_DEBUG_PRINT) queue_print(&q);
    if (q.indexIn != q.indexOut) {
        printf("failed. (should have wrapped around)\n\r");
        return QUEUE_FAIL;
    }

    printf("passed.\r\n");

    ////////////////////////////
    // Now that it's wrapped, //
    //  try popping back to   //
    //  the unwrapped state   //
    ////////////////////////////
    printf("- It should pop, then be unwrapped...");
    for (; i>(QUEUE_TEST_SIZE-1); --i) {
        queue_pop(&q);

        if (QUEUE_DEBUG_PRINT) queue_print(&q);
    }

    if (QUEUE_DEBUG_PRINT) printf("\n\r** ITERATE THROUGH DATA **\n\r");
    for (i=0; i<queue_elementCount(&q); i++) {
        if (i) {
            // later elements should be greater numerically
            if (!(queue_readElementAt(&q, i) > queue_readElementAt(&q, (i-1)))) {
                printf("failed. (elements out of order)\n\r");
                return QUEUE_FAIL;
            }
        }
        if (QUEUE_DEBUG_PRINT) printf("[%u]: %f\r\n", i, queue_readElementAt(&q, i));
    }

    printf("passed.\r\n");

    queue_garbageCollect(&q);

    return QUEUE_PASS;
}

// ----------------------------------------------------------------------------
// Helper Functions
// ----------------------------------------------------------------------------

queue_index_t queue_getIndex(queue_t* q, queue_index_t index) {
    return (index + q->indexOut) % queue_size(q);
}

void queue_incrementIndexIn(queue_t* q) {
    if (q->indexIn == (queue_size(q) - 1)) {
        // time to wrap!
        q->indexIn = 0;
    } else {
        ++q->indexIn;
    }
}

void queue_incrementIndexOut(queue_t* q) {
    if (q->indexOut == (queue_size(q) - 1)) {
        // time to wrap!
        q->indexOut = 0;
    } else {
        ++q->indexOut;
    }
}

// ----------------------------------------------------------------------------
// Hutching's Torture Test Code
// ----------------------------------------------------------------------------

#define SMALL_QUEUE_SIZE 10
#define SMALL_QUEUE_COUNT 10
static queue_t smallQueue[SMALL_QUEUE_COUNT];
static queue_t largeQueue;

// smallQueue[SMALL_QUEUE_COUNT-1] contains newest value, smallQueue[0] contains oldest value.
// Thus smallQueue[0](0) contains oldest value. smallQueue[SMALL_QUEUE_COUNT-1](SMALL_QUEUE_SIZE-1) contains newest value.
// Presumes all queue come initialized full of something (probably zeros).
static double popAndPushFromChainOfSmallQueues(double input) {
  // Grab the oldest value from the oldest small queue before it is "pushed" off.
  double willBePoppedValue = queue_readElementAt(&(smallQueue[0]), 0);
  // Sequentially pop from the next newest queue and push into next oldest queue.
  int i;
  for (i=0; i<SMALL_QUEUE_COUNT-1; i++) {
    queue_overwritePush(&(smallQueue[i]), queue_pop(&(smallQueue[i+1])));
  }
  queue_overwritePush(&(smallQueue[SMALL_QUEUE_COUNT-1]), input);
  return willBePoppedValue;
}

static bool compareChainOfSmallQueuesWithLargeQueue(uint16_t iterationCount) {
  bool success = true;
  static uint16_t oldIterationCount;
  static bool firstPass = true;
  // Start comparing the oldest element in the chain of small queues, and the large queue
  // and move towards the newest values.
  uint16_t smallQIdx;
  uint16_t smallQEltIdx;

  for (smallQIdx=0; smallQIdx<SMALL_QUEUE_COUNT; smallQIdx++) {
    for (smallQEltIdx=0; smallQEltIdx<SMALL_QUEUE_SIZE; smallQEltIdx++) {
      double smallQElt = queue_readElementAt(&(smallQueue[smallQIdx]), smallQEltIdx);
      double largeQElt = queue_readElementAt(&largeQueue, (smallQIdx*SMALL_QUEUE_SIZE) + smallQEltIdx);
      if (smallQElt != largeQElt) {
    if (firstPass || (iterationCount != oldIterationCount)) {
      printf("Iteration:%d\n\r", iterationCount);
      oldIterationCount = iterationCount;
      firstPass = false;
    }
    printf("largeQ(%d):%lf", (smallQIdx*SMALL_QUEUE_SIZE) + smallQEltIdx, largeQElt);
    printf(" != ");
    printf("smallQ[%d](%d): %lf\n\r", smallQIdx, smallQEltIdx, smallQElt);
        success = false;
      }
    }
  }
  return success;
}

#define TEST_ITERATION_COUNT 105
#define FILLER 5
bool queue_runTortureTest() {
  bool success = true;  // Be optimistic.
  // Let's make this a real torture test by testing queues against themselves.
  // Test the queue against an array to make sure there is agreement between the two.
  double testData[SMALL_QUEUE_SIZE + FILLER];
  queue_t q;
  queue_init(&q, SMALL_QUEUE_SIZE);
  // Generate test values and place the values in both the array and the queue.
  int i, j;
  for (i=0; i<SMALL_QUEUE_SIZE + FILLER; i++) {
    double value = (double)rand()/(double)RAND_MAX;
    queue_overwritePush(&q, value);
    testData[i] = value;
  }
  // Everything is initialized, compare the contents of the queue against the array.
  for (i=0; i<SMALL_QUEUE_SIZE; i++) {
    double qValue = queue_readElementAt(&q, i);
    if (qValue != testData[i+FILLER]) {
      printf("testData[%d]:%lf != queue_readElementAt(&q, %d):%lf\n\r", i, testData[i+FILLER], i+FILLER, qValue);
      success = false;
    }
  }
  if (!success) {
    printf("Test 1 failed. Array contents not equal to queue contents.\n\r");
  } else {
    printf("Test 1 passed. Array contents match queue contents.\n\r");
  }
  success = true;  // Remain optimistic.
  // Test 2: test a chain of 5 queues against a single large queue that is the same size as the cumulative 5 queues.
  for (i=0; i<SMALL_QUEUE_COUNT; i++)
    queue_init(&(smallQueue[i]), SMALL_QUEUE_SIZE);
  for (i=0; i<SMALL_QUEUE_COUNT; i++) {
    for (j=0; j<SMALL_QUEUE_SIZE; j++)
      queue_overwritePush(&(smallQueue[i]), 0.0);
  }
  queue_init(&largeQueue, SMALL_QUEUE_SIZE * SMALL_QUEUE_COUNT);
  for (i=0; i<SMALL_QUEUE_SIZE*SMALL_QUEUE_COUNT; i++)
    queue_overwritePush(&largeQueue, 0.0);
  for (i=0; i<TEST_ITERATION_COUNT; i++) {
    double newInput = (double)rand()/(double)RAND_MAX;
    popAndPushFromChainOfSmallQueues(newInput);
    queue_overwritePush(&largeQueue, newInput);
    if (!compareChainOfSmallQueuesWithLargeQueue(i)) {  // i is passed to print useful debugging messages.
      success = false;
    }
  }

  if (success)
    printf("Test 2 passed. Small chain of queues behaves identical to single large queue.\n\r");
  else
    printf("Test 2 failed. The content of the chained small queues does not match the contents of the large queue.\n\r");
  return success;
}
