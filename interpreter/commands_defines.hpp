#pragma once

#define NO_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command() {} \
            ~name##Command() {} \
                                \
            void exec(State&) const override; \
                                                    \
            static Command* create(const std::vector<std::string>& args) { \
                if (args.size() != 0) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                return new name##Command(); \
            } \
    };

#define INT_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command(int value) : value(value) {} \
            ~name##Command() {} \
                                \
            void exec(State&) const override; \
                                                    \
            static Command* create(const std::vector<std::string>& args) { \
                if (args.size() != 1) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                int value; \
                try { \
                    value = std::stoi(args[0]); \
                } catch (const std::invalid_argument&) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                return new name##Command(value); \
            } \
              \
        private: \
            int value; \
    };

#define REG_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command(const RegisterName& reg) : reg(reg) {} \
            ~name##Command() {} \
                                \
            void exec(State&) const override; \
                                                    \
            static Command* create(const std::vector<std::string>& args) { \
                if (args.size() != 1) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                return new name##Command(RegisterName(args[0])); \
            } \
              \
        private: \
            RegisterName reg; \
    };

#define LABEL_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command(const std::string& label) : label(label) {} \
            ~name##Command() {} \
                                \
            void exec(State&) const override; \
                                                    \
            static Command* create(const std::vector<std::string>& args) { \
                if (args.size() != 1) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                return new name##Command(args[0]); \
            } \
              \
        private: \
            std::string label; \
    };

#define COMMAND_CREATE_FUNCTION(name) name##Command::create
