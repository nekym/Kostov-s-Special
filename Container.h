#pragma once

#include <exception>


class EmptyContainerException : public std::exception {
public:
	virtual const char* what() const {
		return "Error: container is empty";
	}
};

class NoSuchElementException : public std::exception {
public:
	virtual const char* what() const {
		return "Error: index is incorrect, no such element";
	}
};

//���������� ������������ �� ���� ����������� ������
template <typename T>
class Container {
public:
	Container() {
		m_head = NULL;
		m_size = 0;
	}

	void AddEnd(T data) {
		//������� ����� �������
		Unit * newElem = new Unit;
		newElem->m_data = data;
		newElem->m_next = NULL;
	
		if (m_head != NULL) {
			//���� ������ �� ����, �� ���� ��������� ������� � ������ ���������� �� ���������
			Unit * element = m_head;
			while (element->m_next != NULL)
				element = element->m_next;
			element->m_next = newElem;
		} else {
			//���� �� ��� ���� ����
			m_head = newElem;
		}
		++m_size;
	}

	void AddTop(T data) {
		//������� ����� �������
		Unit * newElem = new Unit;
		newElem->m_data = data;
		newElem->m_next = m_head;
		//� ������ ����� ������� ��������
		m_head = newElem;
		++m_size;
	}

	void DeleteEnd() {
		if (m_head == NULL)
			return;
		if (m_head->m_next == NULL) {
			//���� ����� 1 �������
			delete m_head;
			m_head = NULL;
			m_size = 0;
		}
		else {
			//������ ��������� �� ������� � ���������� �������
			Unit * current = m_head;
			Unit * previous = NULL;
			//���� � ���������� ��������, ��������� �������������
			while (current->m_next != NULL) {
				previous = current;
				current = current->m_next;
			}
			//������� ���������, � �������������� �������� ��������� �� ���������.
			delete current;
			previous->m_next = NULL;
			--m_size;
		}
	}

	void DeleteTop() {
		if (m_head == NULL)
			return;
		//��������� �� ������ ������� ������������ � ��������� �� ������ � ������� ������
		Unit * newHead = m_head->m_next;
		delete m_head;
		m_head = newHead;
		--m_size;
	}

	T GetEnd() const {
		if (m_head == NULL)
			throw EmptyContainerException();

		//���� ��������� �������
		Unit * element = m_head;
		while (element->m_next != NULL)
			element = element->m_next;
		
		return element->m_data;
	}

	T GetTop() const {
		if (m_head == NULL)
			throw EmptyContainerException();

		return m_head->m_data;
	}

	T& operator [] (const int index) {
		if (index >= m_size || index < 0)
			throw NoSuchElementException();
		//���� �� ���������, ���� �� ������ �� ������� ������
		int ind = 0;
		Unit * element = m_head;
		while (ind != index) {
			element = element->m_next;
			++ind;
		}

		return element->m_data;
	}

	int Size() const{
		return m_size;
	}

	bool IsEmpty() const {
		return m_size == 0 ? true : false;
	}

	void Clear() {
		if (m_head == NULL) return;

		Unit * current = m_head;
		Unit * previous;

		while (current->m_next != NULL) {
			previous = current;
			current = current->m_next;
			delete previous;
		}
		delete current;
		m_head = NULL;
		m_size = 0;
	}

private:
	//������ ������� ���������� ������� �������������� �� �������� ���� T
	//� ������ �� ��������� ������� (��� NULL, ���� ���������� ���)
	struct Unit {
		T m_data;
		Unit * m_next;
	};

	Unit * m_head;
	int m_size;
};

