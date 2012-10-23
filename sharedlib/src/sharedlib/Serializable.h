#ifndef SERIALIZABLE_H
#define	SERIALIZABLE_H

class Serializable {
    virtual void fromJson() = 0;
    virtual void toJson() = 0;
};

#endif	/* SERIALIZABLE_H */
