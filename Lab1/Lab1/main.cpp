#include <iostream>

using namespace std;

class Color
{
public:
    int get_r()
    {
        return r;
    }

    int get_g()
    {
        return g;
    }

    int get_b()
    {
        return b;
    }

    int get_h()
    {
        return h;
    }

    float get_s()
    {
        return s;
    }

    float get_v()
    {
        return v;
    }
    
    void set_RGB(int r, int g, int b)
    {
        if (!is_valid_RGB(r))
        {
            throw out_of_range("R value must be between 0 and 255");
        }
        this->r = r;
        
        if (!is_valid_RGB(g))
        {
            throw out_of_range("G value must be between 0 and 255");
        }
        this->g = g;
        
        if (!is_valid_RGB(b))
        {
            throw out_of_range("B value must be between 0 and 255");
        }
        this->b = b;

        RGB_to_HSV(r, g, b);
    }
    
    void set_HSV(int h, float s, float v)
    {
        if (!is_valid_H(h))
        {
            throw out_of_range("H value must be between 0 and 360");
        }
        this->h = h;
        
        if (!is_valid_SV(s))
        {
            throw out_of_range("S value must be between 0 and 1");
        }
        this->s = s;
        
        if (!is_valid_SV(v))
        {
            throw out_of_range("V value must be between 0 and 1");
        }
        this->v = v;
        
        HSV_to_RGB(h, s, v);
    }
    
    void print()
    {
        cout << "R = " << r << "\t G = " << g << "\t B = " << b << endl;
        cout << "H = " << h << "°\t S = " << s << "\t V = " << v << endl;
    }

private:
    int r;
    int g;
    int b;
    int h;
    float s;
    float v;
    
    bool is_valid_RGB(int value)
    {
        return value >= 0 && value <= 255;
    }
    
    bool is_valid_H(int h)
    {
        return h >= 0 && h <= 360;
    }
    
    bool is_valid_SV(float value)
    {
        return value >= 0 && value <= 1;
    }
    
    void RGB_to_HSV(int r, int g, int b)
    {
        float r_norm = r / 255.0f;
        float g_norm = g / 255.0f;
        float b_norm = b / 255.0f;
        
        float maximum = max({r_norm, g_norm, b_norm});
        float minimum = min({r_norm, g_norm, b_norm});
        float diff = maximum - minimum;
        
        v = maximum;
        
        maximum == 0 ? s = 0 : s = diff / maximum;
        
        if (diff == 0)
        {
            h = 0;
        }
        
        else if (maximum == r_norm)
        {
            h = ((int)((g_norm - b_norm) / diff)) % 6;;
        }
        
        else if (maximum == g_norm)
        {
            h = ((b_norm - r_norm) / diff) + 2;
        }
        
        else if (maximum == b_norm)
        {
            h = ((r_norm - g_norm) / diff) + 4;
        }
        
        h *= 60;
        
        if (h < 0)
        {
            h += 360;
        }
    }

    void HSV_to_RGB(int h, float s, float v)
    {
        float c = s * v;
        float x = c * (1 - abs((h / 60) % 2 - 1));
        float m = v - c;
        float r1 = 0;
        float g1 = 0;
        float b1 = 0;
        
        if (h >= 0 && h < 60)
        {
            r1 = c;
            g1 = x;
        }
        
        else if (h >= 60 && h < 120)
        {
            r1 = x;
            g1 = c;
        }
        
        else if (h >= 120 && h < 180)
        {
            g1 = c;
            b1 = x;
        }
        
        else if (h >= 180 && h < 240)
        {
            g1 = x;
            b1 = c;
        }
        
        else if (h >= 240 && h < 300)
        {
            r1 = x;
            b1 = c;
        }
        
        else if (h >= 300 && h < 360)
        {
            r1 = c;
            b1 = x;
        }
        
        r = (r1 + m) * 255;
        g = (g1 + m) * 255;
        b = (b1 + m) * 255;
    }
};

int main()
{
    Color color;
    color.set_RGB(255, 0, 0);
    color.print();
    color.set_HSV(0, 0, 0.501961);
    color.print();
    return 0;
}
