#!/bin/bash -e
# RESULT=`./tests/test_tp "ช่วยให้นักพัฒนา english สามารถเรียกใช้งาน"`
# RESULT=`./tests/test_tp 'เทกระจาด'`
# RESULT=`./tests/test_tp 'เทกระจาด'`
# RESULT=`./tests/test_tp 'CHINA:โกลด์แมน แซคส์ปรับเพิ่มคาดการณ์จีดีพีจีนขึ้นเป็น 6% ในปีนี้ จากที่คาดไว้ก่อ'`

# RESULT=`./tests/test_tp 'ช่วยให้นักพัฒนา storm สามารถเรียกใช้งาน'`
# RESULT=`./tests/test_tp 'จบ--"]}]}]},{"type":"p","children":["    Eikon source text  "]}]}'`
# RESULT=`./tests/test_tp 'ซึ่งมีความก้าวหน้าใหม่ในการฟื้นตัวจากภาวะตกต่ำที่เกิดขึ้นหลายเดือน'`
RESULT=`./tests/test_tp 'การฟื้นฟูงบดุลของภาคเอกชนและส่วนบุคคลที่เสียหายไปในช่วงโรคระบาดนั้นจะต้องใช้เวลา'`
# RESULT=`./tests/test_tp 'เว็บ'`
# RESULT=`./tests/test_tp '{"type":"root","children":[{"type":"list","children":[{"type":"*","children":[{"type":"p","children":["โกลด์แมน แซคส์ได้ปรับเพิ่มคาดการณ์จีดีพีของจีนในปีนี้ขึ้นเป็น'`
# RESULT=`./tests/test_tp 'CHINA:โกลด์แมน แซคส์ปรับเพิ่มคาดการณ์จีดีพีจีนขึ้นเป็น 6% ในปีนี้ {"type":"root","children":[{"type":"list","children":[{"type":"*","children":[{"type":"p","children":["โกลด์แมน แซคส์ได้ปรับเพิ่มคาดการณ์จีดีพีของจีนในปีนี้ขึ้นเป็น 6% จากที่คาดไว้ก่อนหน้านี้ที่ 5.5% เนื่องจากการเปิดประเทศอย่างรวดเร็วของจีน"]}]},{"type":"*","children":[{"type":"p","children":["การฟื้นตัวแข็งแกร่งของภาคธุรกิจที่มีความอ่อนไหวต่อการแพร่ระบาดของโควิด-19 และข้อมูลกิจกรรมทางเศรษฐกิจที่ปรับตัวดีขึ้นโดยรวมในช่วง 2 เดือนแรกของปีทำให้มีการปรับเพิ่มคาดการณ์ดังกล่าว"]}]},{"type":"*","children":[{"type":"p","children":["เศรษฐกิจจีนมีการฟื้นตัวทีละน้อยแต่ไม่สม่ำเสมอในเดือนม.ค.และก.พ. แต่นายฟู หลิงฮุ่ย โฆษกสำนักงานสถิติแห่งชาติระบุว่า การฟื้นฟูงบดุลของภาคเอกชนและส่วนบุคคลที่เสียหายไปในช่วงโรคระบาดนั้นจะต้องใช้เวลา "]}]},{"type":"*","children":[{"type":"p","children":["โกลด์แมน แซคส์ยังได้ระบุถึงกิจกรรมที่ดีขึ้นในภาคอสังหาริมทรัพย์ ซึ่งมีความก้าวหน้าใหม่ในการฟื้นตัวจากภาวะตกต่ำที่เกิดขึ้นหลายเดือน ซึ่งเป็นเหตุผลอีกข้อที่ทำให้ปรับขึ้นคาดการณ์"]}]},{"type":"*","children":[{"type":"p","children":["จีนได้กำหนดเป้าหมายการเติบโตทางเศรษฐกิจที่ 5% ในปีนี้ หลังจากที่พลาดเป้าหมายในปีที่แล้วอย่างมีนัยสำคัญ โดยเศรษฐกิจจีนขยายตัวเพียง 3% ในปีที่แล้ว ซึ่งเป็นอัตราต่ำสุดในรอบหลายทศวรรษยกเว้นป 2020 เนื่องจากมาตรการควบคุมโควิด, ภาวะตกต่ำในตลาดอสังหาริมทรัพย์ และภาวะอุปสงค์ต่างประเทศที่ชะลอตัว--จบ--"]}]}]},{"type":"p","children":["    Eikon source text  "]}]}'`

echo $RESULT
# if [[ "$RESULT" == ">>ทดสอบการตัดคำภาษาไทยสำหรับ PostgreSQL Full Text Search<< ทดสอบ|การ|ตัด|คำ|ภาษา|ไทย|สำหรับ| |PostgreSQL| |Full| |Text| |Search|" ]]; then
#     echo -e "\x1B[0;32m Passes.\x1B[0m"
# else
#     echo -e "\x1B[0;31m Failed!!\x1B[0m"
# fi

