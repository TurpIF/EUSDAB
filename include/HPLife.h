#ifndef HPLIFE_H_
#define HPLIFE_H_

#include <life.h>

namespace EUSDAB
{
	class HPLife: public Life
	{
		public:
			HPLife(HPLife &&) = default;
			HPLife(const HPLife &) = default;
			HPLife & operator=(const HPLife &) = default;

			~HPLife();

			HPLife(const Amount & max,
                    const Amount & min = static_cast<Amount>(0));

			bool isAlive() const;
			void receiveDamage(const Amount &);
			void healDamage(const Amount &);

        private:
			Amount _min, _hp, _max;
	};
}

#endif
