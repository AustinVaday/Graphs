/**************************************************************************
* AUTHOR        : Austin Vaday
**************************************************************************/
#ifndef HEAPITEMHEADER_H_
#define HEAPITEMHEADER_H_


template <typename DataType>
class HeapItem
{
     public:
		HeapItem();								// Default Constructor
		HeapItem(DataType newData);
												// Constructor
		~HeapItem();                         	// Destructor
		void setData(DataType newData);         // Set the data item value
		void setItem(const HeapItem<DataType> &item);
												// Set the priority key
												// value and data item value
		DataType getData() const;              	// Return data item

     private:
   		DataType data;                       	// Heap item data store

};
/**************************************************************************
 * Default constructor with base initialization to a type of its own
 *************************************************************************/
template  < typename DataType>
HeapItem<DataType>::HeapItem()
							: data(DataType())
{

}
/**************************************************************************
 * Argumented constructor with base initialization
 *************************************************************************/
template  < typename DataType>
HeapItem<DataType>::HeapItem(DataType newData)
							: data(newData)
{

}
/**************************************************************************
 * Destructor
 *************************************************************************/
template  < typename DataType>
HeapItem<DataType>::~HeapItem()
{

}
///**************************************************************************
// * Set the priority key value
// *************************************************************************/
//template  < typename DataType>
//void HeapItem<DataType>::setKey(KeyType newKey)
//{
//	key = newKey;
//}
/**************************************************************************
 * Set the data item value
 *************************************************************************/
template  < typename DataType>
void HeapItem<DataType>::setData(DataType newData)
{
	data = newData;
}
/**************************************************************************
 * Set the priority key value and data item value
 *************************************************************************/
template  < typename DataType>
void HeapItem<DataType>::setItem(const HeapItem<DataType> &item)
{
	data = item.data;
//	key  = item.key;
}
///**************************************************************************
// * Return item priority
// *************************************************************************/
//template  < typename DataType>
//KeyType HeapItem<DataType>::getKey() const
//{
//	return key;
//}
/**************************************************************************
 * Return data item
 *************************************************************************/
template  < typename DataType>
DataType HeapItem<DataType>::getData() const
{
	return data;
}


#endif /* HEAPITEMHEADER_H_ */
