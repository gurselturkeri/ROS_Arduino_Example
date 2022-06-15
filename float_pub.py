import rospy
from std_msgs.msg import Float64


if __name__ == '__main__':
    try:

        rospy.init_node('deneme')
        pub = rospy.Publisher('value1',Float64,queue_size=10)
        pub2 = rospy.Publisher('value2',Float64,queue_size=10)

        while not rospy.is_shutdown():

            def value1():
                sayi1 = 1.4587

                sayi1_pub = Float64()
                sayi1_pub.data = sayi1
                return pub.publish(sayi1_pub)

            def value2():
                sayi2 = 541

                sayi2_pub = Float64()
                sayi2_pub.data = sayi2
                return pub2.publish(sayi2_pub)
            value2()
            value1()
            
        rospy.spin()


    except rospy.ROSInterruptException:
        pass        

    
