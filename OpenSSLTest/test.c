#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <openssl/md5.h>
#include <openssl/rand.h>

void test_md5(void *data, int size)
{
  MD5_CTX ctx;
  unsigned char md5[16];
  MD5_Init(&ctx);
  MD5_Update(&ctx, data, size);
  MD5_Final(md5, &ctx);
  for (int i = 0; i < 16; i++)
  {
    printf(md5[i] < 0x10 ? "0%x" : "%x", md5[i]);
  }
  printf("\n");
}

// These don't need to do anything if you don't have anything for them to do.
static void stdlib_rand_cleanup() {}
static void stdlib_rand_add(const void *buf, int num, double add_entropy) {}
static int stdlib_rand_status() { return 1; }

// Seed the RNG.  srand() takes an unsigned int, so we just use the first
// sizeof(unsigned int) bytes in the buffer to seed the RNG.
static void stdlib_rand_seed(const void *buf, int num)
{
  assert(num >= sizeof(unsigned int));
  srand(*((unsigned int *)buf));
}

// Fill the buffer with random bytes.  For each byte in the buffer, we generate
// a random number and clamp it to the range of a byte, 0-255.
static int stdlib_rand_bytes(unsigned char *buf, int num)
{
  for (int index = 0; index < num; ++index)
  {
    buf[index] = rand() % 256;
  }
  return 1;
}

// Create the table that will link OpenSSL's rand API to our functions.
RAND_METHOD stdlib_rand_meth = {
    stdlib_rand_seed,
    stdlib_rand_bytes,
    stdlib_rand_cleanup,
    stdlib_rand_add,
    stdlib_rand_bytes,
    stdlib_rand_status};

// This is a public-scope accessor method for our table.
RAND_METHOD *RAND_stdlib() { return &stdlib_rand_meth; }

int main(int argc, char **argv)
{

  RAND_set_rand_method(RAND_stdlib());
  printf("test-md5 start \n");
  if (argc < 2)
  {
    RAND_seed("0123456789", 10);
  }
  else
  {
    RAND_seed(argv[1], strlen(argv[1]));
  }
  char buffer[32];
  int rc = 1;
  while (rc = RAND_pseudo_bytes(buffer, sizeof(buffer)))
  {
    test_md5(buffer, 32);
    sleep(2);
  }

  if (rc != 1)
  {
    printf("generate  random value error.\n");
    return -1;
  }
  return 0;
}