all:
	g++ consumer.cpp -o consumer
	g++ producer.cpp -o producer
clean:
	$(RM) ./consumer
	$(RM) ./producer
	
