CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O3 -I.
LDFLAGS := -lm

# Цели для тестов
GEODETIC_TARGET := geodetic_test
ATMOSPHERE_TARGET := atmosphere_test

# Основная цель - собирает все тесты
all: $(GEODETIC_TARGET) $(ATMOSPHERE_TARGET)

# Сборка геодезического теста
$(GEODETIC_TARGET): geodetic.cpp test_geodetic.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Сборка теста атмосферы
$(ATMOSPHERE_TARGET): test_atmosphere.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Очистка
clean:
	rm -f $(GEODETIC_TARGET) $(ATMOSPHERE_TARGET) *.o

# Запуск всех тестов
test: $(GEODETIC_TARGET) $(ATMOSPHERE_TARGET)
	@echo "============================================="
	@echo " RUNNING GEODETIC TESTS"
	@echo "============================================="
	@./$(GEODETIC_TARGET)
	@echo
	@echo "============================================="
	@echo " RUNNING ATMOSPHERE TESTS"
	@echo "============================================="
	@./$(ATMOSPHERE_TARGET)

.PHONY: all clean test