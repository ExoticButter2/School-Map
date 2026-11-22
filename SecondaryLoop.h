#ifndef SECONDARY_LOOP
#define SECONDARY_LOOP

void AddFunction(void (*)());
void RemoveFunction(void (*)());

void InitializeSecondaryLoop();
void SecondaryLoop(void*);

#endif