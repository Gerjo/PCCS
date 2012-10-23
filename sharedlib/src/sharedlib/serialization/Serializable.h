#ifndef SERIALIZABLE_H
#define	SERIALIZABLE_H

class Serializable {
    virtual void fromData(Data& data) = 0;
    virtual void toData(Data& data) = 0;
};

#endif	/* SERIALIZABLE_H */
