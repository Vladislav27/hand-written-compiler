#ifndef HAND_WRITTEN_COMPILER_LINEHANDLER_H
#define HAND_WRITTEN_COMPILER_LINEHANDLER_H


namespace Comp
{
    class LineHandler {
    public:
        unsigned int getPosition(unsigned int step);
        void refreshValues();
        unsigned int getLine();

    private:
        unsigned int position = 1;
        unsigned int currentLine = 1;
    };
}


#endif //HAND_WRITTEN_COMPILER_LINEHANDLER_H
