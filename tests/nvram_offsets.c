#include <assert.h>
#include <stdlib.h>

#include "Tpm.h"

/* from Global.h */
extern BYTE s_indexOrderlyRam[RAM_INDEX_SPACE];

int main(void)
{
    PERSISTENT_DATA pd;

    /* Check size of ppList that expands with new commands */
#define PD_PP_LIST_EXP_SIZE 14
    if (sizeof(pd.ppList) != PD_PP_LIST_EXP_SIZE) {
        fprintf(stderr,
                "sizeof(PERSISTENT_DATA.ppList) does not have expecte size "
                "of %u bytes but %zu bytes\n",
                PD_PP_LIST_EXP_SIZE, sizeof(pd.ppList));
        return EXIT_FAILURE;
    }

    /* Check size of auditCommands that expands with new commands */
#define PD_AUDIT_COMMANDS_EXP_SIZE 14
    if (sizeof(pd.auditCommands) != PD_AUDIT_COMMANDS_EXP_SIZE) {
        fprintf(stderr,
                "sizeof(PERSISTENT_DATA.auditCommands) does not have expecte size "
                "of %u bytes but %zu bytes\n",
                PD_AUDIT_COMMANDS_EXP_SIZE, sizeof(pd.auditCommands));
        return EXIT_FAILURE;
    }

    /* ensure that the NVRAM offset of NV_USER_DYNAMIC is at the expected
       location so that there's enough memory for re-constructing NVRAM
       indices etc. into the NVRAM */
#define NV_INDEX_RAM_DATA_EXP_OFFSET 5120
    if (NV_INDEX_RAM_DATA != NV_INDEX_RAM_DATA_EXP_OFFSET) {
        /* If this ever changes due to growth of the preceding data
         * structure, we need to adjust the total NVRAM memory size
         * for the architecture where this changed (or have all
         * architectures use the same offset.
         */
        fprintf(stderr,
                "NV_INDEX_RAM_DATA not at expected offset %u but at %u\n",
                 NV_INDEX_RAM_DATA_EXP_OFFSET, (unsigned int)NV_INDEX_RAM_DATA);
        return EXIT_FAILURE;
    }

#define NV_USER_DYNAMIC_EXP_OFFSET (5120 + 512)
    if (NV_USER_DYNAMIC != NV_USER_DYNAMIC_EXP_OFFSET) {
        fprintf(stderr,
                "NV_USER_DYNAMIC not at expected offset %u but at %u\n",
                NV_USER_DYNAMIC_EXP_OFFSET, (unsigned int)NV_USER_DYNAMIC);
        return EXIT_FAILURE;
    }

    /*
     * OBJECTs are directly written into NVRAM. We have to make sure that the
     * size of the OBJECT is the same on all architectures so that a full
     * NVRAM fits on all architectures
     */
#define OBJECT_EXP_SIZE 1896
    if (sizeof(OBJECT) != OBJECT_EXP_SIZE) {
        fprintf(stderr, "sizeof(OBJECT) does not have expected size of %u bytes"
                        "but %zu bytes\n", OBJECT_EXP_SIZE, sizeof(OBJECT));
        return EXIT_FAILURE;
    }

    /* Same for NV_INDEX */
#define NV_INDEX_EXP_SIZE 148
    if (sizeof(NV_INDEX) != NV_INDEX_EXP_SIZE) {
        fprintf(stderr,
                "sizeof(NV_INDEX) does not have expected size of %u bytes"
                "but %zu bytes\n", NV_INDEX_EXP_SIZE, sizeof(NV_INDEX));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
