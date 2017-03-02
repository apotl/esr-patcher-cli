#include "Patcher.h"
#include "defines.h"

void printUsage(char* binName) {
    printf("usage: %s", binName);
    printf(" [-u] path/to/ps2_iso\n");
}

int main (int argc, char** argv) {

    if (argc < 2 || argc > 3
        || (argc == 3 && strcmp(argv[1], "-u") == 0 && strcmp(argv[2], "-u") == 0)
        ) {

        printUsage(argv[0]);
        return -1;
    }

    bool unpatch = false;
    char* isoPath;

    if (argc == 3) {
        unpatch = true;
        if (strcmp(argv[1],"-u") == 0)
            isoPath = argv[2];
        else if (strcmp(argv[2],"-u") == 0)
            isoPath = argv[1];
        else
            printUsage(argv[0]);
    }
    else if (argc == 2) {
        isoPath = argv[1];
    }

    CPatcher* patcher = new CPatcher();

    eFileErr result;

    if (unpatch) {
        result = (eFileErr)patcher->doUnPatch(isoPath);
    }
    else {
        result = (eFileErr)patcher->doPatch(isoPath);
    }

    switch (result) {
        case ESR_FILE_ALREADY_PATCHED:
            printf("iso already patched\n");
            break;
        case ESR_FILE_CANNOT_OPEN:
            printf("cannot open iso for reading\n");
            break;
        case ESR_FILE_NO_UDF_DESCRIPTOR:
            printf("no udf descriptor on iso\n");
            break;
        case ESR_FILE_NOT_PATCHED:
            printf("iso already not patched\n");
            break;
        case ESR_FILE_OK:
            printf("ok!\n");
            break;
        case ESR_FILE_WRONG_FORMAT:
            printf("iso is wrong format\n");
            break;
        default:
            break;
    }

    return 0;
}